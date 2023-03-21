import numpy as np


class Dense():
    def __init__(self, n_x, n_y, seed=1):
        self.n_x = n_x
        self.n_y = n_y
        self.seed = seed
        self.initialize_parameters()
        self.name="dense"
        

    def initialize_parameters(self):
        """
        Argument:
        self.n_x -- size of the input layer
        self.n_y -- size of the output layer
        self.parameters -- python dictionary containing your parameters:
                           W -- weight matrix of shape (n_y, n_x)
                           b -- bias vector of shape (n_y, 1)
        """
        np.random.seed(self.seed)

        ### PASTE YOUR CODE HERE ###
        ### START CODE HERE ### 
        limit = np.sqrt(6 / float(self.n_y + self.n_x))
        W = np.random.uniform(low=-limit, high=limit, size=(self.n_y, self.n_x))
        b = np.zeros(shape=(self.n_y, 1))
        ### END CODE HERE ###

        assert(W.shape == (self.n_y, self.n_x))
        assert(b.shape == (self.n_y, 1))

        self.parameters = {"W": W, "b": b}

    def forward(self, A):
        """
        Implement the linear part of a layer's forward propagation.

        Arguments:
        A -- activations from previous layer (or input data): (size of previous layer, number of examples)
        self.cache -- a python tuple containing "A", "W" and "b" ; stored for computing the backward pass efficiently

        Returns:
        Z -- the input of the activation function, also called pre-activation parameter 
        """

        ### PASTE YOUR CODE  ###
        ### START CODE HERE ### 
        Z = np.dot(self.parameters["W"], A) + self.parameters["b"]
        self.cache = (A, self.parameters["W"], self.parameters["b"])
        ### END CODE HERE ###
        
        assert(Z.shape == (self.parameters["W"].shape[0], A.shape[1]))
        
        return Z

    def backward(self, dZ):
        """
        Implement the linear portion of backward propagation for a single layer (layer l)

        Arguments:
        dZ -- Gradient of the cost with respect to the linear output (of current layer l)
        self.cache -- tuple of values (A_prev, W, b) coming from the forward propagation in the current layer
        self.dW -- Gradient of the cost with respect to W (current layer l), same shape as W
        self.db -- Gradient of the cost with respect to b (current layer l), same shape as b

        Returns:
        dA_prev -- Gradient of the cost with respect to the activation (of the previous layer l-1), same shape as A_prev

        """
        A_prev, W, b = self.cache
        m = A_prev.shape[1]

        ### PASTE YOUR CODE HERE ###
        ### START CODE HERE ###
        self.dW = np.dot(dZ, A_prev.T) / m
        self.db = np.sum(dZ, axis=1, keepdims=True) / m
        dA_prev = np.dot(W.T, dZ)
        ### END CODE HERE ###

        
        assert (dA_prev.shape == A_prev.shape)
        assert (self.dW.shape == self.parameters["W"].shape)
        assert (self.db.shape == self.parameters["b"].shape)
        
        return dA_prev

    def update(self, learning_rate):
        """
        Update parameters using gradient descent
        
        Arguments:
        learning rate -- step size
        """

        ### PASTE YOUR CODE HERE ###
        ### START CODE HERE ###
        self.parameters["W"] -= learning_rate*self.dW
        self.parameters["b"] -= learning_rate*self.db
        ### END CODE HERE ###