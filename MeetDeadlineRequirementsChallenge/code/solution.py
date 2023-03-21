"""
This demo aims to help player running system quickly by using the pypi library simple-emualtor https://pypi.org/project/simple-emulator/.
"""
from cmath import inf
from simple_emulator import CongestionControl

# We provided a simple algorithms about packet selection to help you being familiar with this competition.
# In this example, it will select the packet according to packet's created time first and radio of rest life time to deadline secondly.
from simple_emulator import BlockSelection
from simple_emulator import Reno

import numpy as np;

# for tf version < 2.0
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.autograd import Variable
import random

np.random.seed(2)
torch.manual_seed(1)

EVENT_TYPE_FINISHED='F'
EVENT_TYPE_DROP='D'
EVENT_TYPE_TEMP='T'
config = {'USE_CWND': True, 'ENABLE_LOG': True}

class Net(nn.Module):
    '''
    3-layer neural network implemented by torch
    '''
    def __init__(self,
                 N_STATES=10,
                 N_ACTIONS=5,
                 N_HIDDEN=30):

        super(Net, self).__init__()

        self.fc1 = nn.Linear(N_STATES, N_HIDDEN)
        self.fc1.weight.data.normal_(0, 0.1)  # initialization
        self.out = nn.Linear(N_HIDDEN, N_ACTIONS)
        self.out.weight.data.normal_(0, 0.1)  # initialization


    def forward(self, x):
        x = self.fc1(x)
        x = F.relu(x)
        actions_value = self.out(x)
        return actions_value


class DQN(object):
    def __init__(self,
                 N_STATES=10,
                 N_ACTIONS=5,
                 LR=0.01,
                 GAMMA=0.9,
                 TARGET_REPLACE_ITER=100,
                 MEMORY_CAPACITY=200,
                 BATCH_SIZE=32
                 ):

        self.N_STATES = N_STATES
        self.N_ACTIONS = N_ACTIONS
        self.LR = LR
        # self.EPSILON = EPSILON
        self.GAMMA = GAMMA
        self.TARGET_REPLACE_ITER = TARGET_REPLACE_ITER
        self.MEMORY_CAPACITY = MEMORY_CAPACITY
        self.BATCH_SIZE = BATCH_SIZE

        self.eval_net = Net(self.N_STATES, self.N_ACTIONS)
        self.target_net = Net(self.N_STATES, self.N_ACTIONS)

        self.learn_step_counter = 0  # For target update timing
        self.memory_counter = 0  # For recording old states and reward
        self.memory = np.zeros((self.MEMORY_CAPACITY, self.N_STATES * 2 + 2))  # Initial size of memory
        self.optimizer = torch.optim.Adam(self.eval_net.parameters(), lr=LR)  # Torch's optimizer
        self.loss_func = nn.MSELoss()  # Error formula


    def choose_action(self, x):
        x = Variable(torch.unsqueeze(torch.FloatTensor(x), 0))
        # Only enter one sample here
        actions_value = self.eval_net.forward(x)
        action = torch.max(actions_value, 1)[1].data.numpy()[0]  # return the argmax
        return action


    def store_transition(self, s, a, r, s_):
        transition = np.hstack((s, [a, r], s_))
        # If the memory bank is full, overwrite the old data
        index = self.memory_counter % self.MEMORY_CAPACITY
        self.memory[index, :] = transition
        self.memory_counter += 1


    def learn(self):
        # Parameter update of target net 
        if self.learn_step_counter % self.TARGET_REPLACE_ITER == 0:
            self.target_net.load_state_dict(self.eval_net.state_dict())
        self.learn_step_counter += 1

        # Extract batch data from memory
        sample_index = np.random.choice(self.MEMORY_CAPACITY, self.BATCH_SIZE)
        b_memory = self.memory[sample_index, :]
        b_s = Variable(torch.FloatTensor(b_memory[:, :self.N_STATES]))
        b_a = Variable(torch.LongTensor(b_memory[:, self.N_STATES:self.N_STATES+1].astype(int)))
        b_r = Variable(torch.FloatTensor(b_memory[:, self.N_STATES+1:self.N_STATES+2]))
        b_s_ = Variable(torch.FloatTensor(b_memory[:, -self.N_STATES:]))

        # For the action b_a that has been done, 
        # select the value of q_eval, (q_eval originally has the value of all actions)
        q_eval = self.eval_net(b_s).gather(1, b_a)  # shape (batch, 1)

        q_next = self.target_net(b_s_).detach()  # q_next does not perform reverse transfer error, so detach
        q_target = b_r + self.GAMMA * q_next.max(1)[0].reshape(-1, 1)  # shape (batch, 1)
        loss = self.loss_func(q_eval, q_target)

        # Calculate, update eval net
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

# change every EPISODE times
EPISODE = 50 
# send rate, lost rate *2, rtt sample
N_F = 1 + 2 + 2 + EPISODE
# 1.4,1.1,0.4
N_A = 3 
# random choose
Lambda_init = 0.9
# decline Lambda after random_counter 
random_counter_init = 100 
# standardlize to 1
MAX_BANDWITH = 10000
#class RL(CongestionControl):
class RL(Reno):
    def __init__(self):
        super(RL, self).__init__()
        ##
        # the value of congestion window
        self.init_cwnd = 150
        self.cwnd = self.init_cwnd
        # the value of sending rate
        self.init_rate = float(600)
        self.send_rate = self.init_rate
        #elf.send_rate = float("inf")
        # the value of pacing rate
        self.pacing_rate = float("inf")
        # use cwnd
        self.USE_CWND=True

        # for reno
        self.ssthresh = float("inf")
        self.curr_state = "slow_start"
        self.states = ["slow_start", "congestion_avoidance", "fast_recovery"]
        # the number of lost packets
        self.drop_nums = 0
        # the number of acknowledgement packets
        self.ack_nums = 0

        # current time
        self.cur_time = -1
        # the value of cwnd at last packet event
        self.last_cwnd = 0
        # the number of lost packets received at the current moment
        self.instant_drop_nums = 0
        ##
        self.estimate_latency = inf
        self.drop_sum = 0 
        self.inst_cnt = 0 

        self.USE_CWND= True
        self.cwnd = 2000
        self.send_rate = 500.0

        # list to store the input of "cc_trigger"
        self._input_list = []

        self.counter = 0 # EPISODE counter

        self.result_list = []
        self.latency_list = []
        self.last_state = []
        self.last_action = 1
        self.Lambda = Lambda_init
        self.random_counter = random_counter_init

        self.dqn = DQN(N_STATES=N_F,
                        N_ACTIONS=N_A,
                        LR=0.01,
                        GAMMA=0.9,
                        TARGET_REPLACE_ITER=100,
                        MEMORY_CAPACITY=500,
                        BATCH_SIZE=32
                    )

        self.last_state.append(self.send_rate/MAX_BANDWITH)
        self.last_state.extend([0]*4)
        for i in range(EPISODE):
            self.last_state.append(0)
        
        # update in 2020-7-30
        self.event_nums = 0
        self.event_lost_nums = 0
        self.event_ack_nums = 0

    def estimate_bandwidth(self, cur_time, event_info):
        # append the input, help the estimator to do long-term decisions
        self._input_list.append([cur_time, event_info])

        event_type = event_info["event_type"]
        event_time = cur_time

        # Preparing for the bandwidth estimator's decision
        self.latency_list.append(event_info["packet_information_dict"]["Latency"])
        self.event_nums += 1

        if event_type == EVENT_TYPE_DROP:
            self.result_list.append(1)
            self.event_lost_nums += 1
        else:
            self.result_list.append(0)
            self.event_ack_nums += 1

        self.counter += 1
        if self.counter == EPISODE: # choose action every EPISODE times
            self.counter = 0
            # print()
            # print("EPISODE: send_rate is {}".format(self.send_rate))
            # print()
            # loss rate
            sum_loss_rate = self.event_lost_nums / self.event_nums
            instant_packet = list(filter(lambda item: self._input_list[-1][0] - item[0] < 1., self._input_list))
            instant_loss_nums = sum([1 for data in instant_packet if data[1]["event_type"] == 'D']) 
            instant_loss_rate = instant_loss_nums / len(instant_packet) if len(instant_packet) > 0 else 0
            # throughput
            sum_rate = self.event_ack_nums / event_time
            instant_ack_packet = list(filter(lambda data:data[1]["event_type"] == 'F', instant_packet))
            instant_rate = len(instant_ack_packet) / (instant_packet[-1][0] - instant_packet[0][0]) if (instant_packet[-1][0] - instant_packet[0][0]) > 0 else 0

            # declining random rate
            self.random_counter-=1
            if self.random_counter <= 0:
                self.Lambda /=2.0
                if self.Lambda < 0.05:
                    self.Lambda = 0.05
                self.random_counter = 50

            # reward
            r = 0
            for i in range(EPISODE):
                if self.result_list[i] == 0:
                    r += self.send_rate * (i+1)
                else:
                    r -= self.send_rate * (i+1)

            # current_state
            s_ = []
            s_.append(self.send_rate/MAX_BANDWITH)
            s_.append(sum_loss_rate)
            s_.append(instant_loss_rate)
            s_.append(sum_rate)
            s_.append(instant_rate)
            for i in range(EPISODE):
                s_.append(self.latency_list[i])
            s_array=np.array(s_)

            # store
            self.dqn.store_transition(self.last_state, self.last_action, r, s_array)
            # choose action
            a = self.dqn.choose_action(s_array)
           
            # exploration
            if random.random() < self.Lambda:
                a = random.randint(0,2)

            # Estimate the current available bandwidth 
            # and adjust the sending rate according to the output of torch model
            if self.send_rate - 500 < 0.00001:
                self.send_rate = MAX_BANDWITH / 2
                a = 0
            elif MAX_BANDWITH - self.send_rate < 1.0000001:
                self.send_rate = MAX_BANDWITH / 2
                a = 2
            elif a == 0:
                self.send_rate *= 1.4
            elif a == 1:
                self.send_rate *= 1.
            else:
                self.send_rate *= 0.4
            self.last_action = a
            # DQN learn
            self.dqn.learn()

            self.last_state = s_
            self.result_list = []
            self.latency_list = []



# Your solution should include packet selection and bandwidth estimator.
# We recommend you to achieve it by inherit the objects we provided and overwritten necessary method.
class MySolution(BlockSelection, RL):

    def select_block(self, cur_time, block_queue):
        self.best_score = 0
        def is_better(block):
            best_block_create_time = best_block.block_info["Create_time"]
            cur_block_create_time = block.block_info["Create_time"]
            # if block is miss ddl
            if (cur_time - cur_block_create_time) >= block.block_info["Deadline"]:
                return False
            if (cur_time - best_block_create_time) >= best_block.block_info["Deadline"]:
                return True
            # create_time & ddl & priority
            priority = {0: 100, 1: 80, 2: 10}
            priority_score = priority[block.block_info["Priority"]]
            
            if(block.block_info["Create_time"] >= cur_time): ddl_score = 0
            else: ddl_score = 100 * (1 - (block.block_info["Create_time"] + block.block_info["Deadline"] - cur_time) / block.block_info["Deadline"])
            
            if (block.block_info["Create_time"] + block.block_info["Deadline"] - cur_time) < self.estimate_latency:
                ddl_score = 0
           
            cur_score = priority_score**2.5 * ddl_score**0.5 / block.block_info["Size"]**1.5 



            ans = cur_score > self.best_score
            self.best_score = max(cur_score, self.best_score)
            return ans

        best_block_idx = -1
        best_block= None
        for idx, item in enumerate(block_queue):
            if best_block is None or is_better(item) :
                best_block_idx = idx
                best_block = item

        return best_block_idx

    
    def cc_trigger(self, cur_time, event_info):
        """
        The part of algorithm to make congestion control, which will be call when sender get an event about acknowledge or lost from reciever.
        See more at https://github.com/AItransCompetition/simple_emulator/tree/master#congestion_control_algorithmpy.
        """
        super().estimate_bandwidth(cur_time, event_info)
        ##reno start
        event_type = event_info["event_type"]
        event_time = cur_time
        ##
        self.estimate_latency = event_info["packet_information_dict"]["Latency"]
        self.inst_cnt +=1

        if self.cur_time < event_time:
            # initial parameters at a new moment
            self.last_cwnd = 0
            self.instant_drop_nums = 0

        # if packet is dropped
        if event_type == EVENT_TYPE_DROP:
            # dropping more than one packet at a same time is considered one event of packet loss 
            ##
            self.drop_sum += 1
            if self.instant_drop_nums > 0:
                return
            self.instant_drop_nums += 1

            # step into fast recovery state
            self.curr_state = self.states[2]
            self.drop_nums += 1
            # clear acknowledgement count
            self.ack_nums = 0
            # Ref 1 : For ensuring the event type, drop or ack?
            self.cur_time = event_time
            if self.last_cwnd > 0 and self.last_cwnd != self.cwnd:
                # rollback to the old value of cwnd caused by acknowledgment first
                self.cwnd = self.last_cwnd
                self.last_cwnd = 0

        # if packet is acknowledged
        elif event_type == EVENT_TYPE_FINISHED:
            # Ref 1
            if event_time <= self.cur_time:
                return
            self.cur_time = event_time
            self.last_cwnd = self.cwnd
            
            # increase the number of acknowledgement packets
            self.ack_nums += 1
            # double cwnd in slow_start state
            if self.curr_state == self.states[0]:
                if self.ack_nums == self.cwnd:
                    self.cwnd *= 2
                    self.ack_nums = 0
                # step into congestion_avoidance state due to exceeding threshhold
                if self.cwnd >= self.ssthresh:
                    self.curr_state = self.states[1]

            # increase cwnd linearly in congestion_avoidance state
            elif self.curr_state == self.states[1]:
                if self.ack_nums == self.cwnd:
                    self.cwnd += 1
                    self.ack_nums = 0
            ## time out: send_delay + latency > deadline -> ss
            if event_info["packet_information_dict"]["Send_delay"] + event_info["packet_information_dict"]["Latency"] > event_info["packet_information_dict"]["Block_info"]["Deadline"]:
                self.cwnd = self.init_cwnd
                self.curr_state = self.states[0]
                self.init_cwnd /=1.4
   
       

        # reset threshhold and cwnd in fast_recovery state
        if self.curr_state == self.states[2]:
            self.ssthresh = max(self.cwnd // 2, self.init_cwnd)
            
            ##
            if self.inst_cnt == 5:
                if self.drop_sum >= 2:
                    self.ssthresh = max(self.cwnd // 2.4, self.init_cwnd)
                self.inst_cnt = 0
                self.drop_sum = 0
            
            self.curr_state = self.states[1]
            self.cwnd = self.ssthresh
        ##reno end
        # set cwnd or sending rate in sender according to bandwidth estimator
        return {
            "cwnd" : self.cwnd,
            "send_rate" : self.send_rate,
        }