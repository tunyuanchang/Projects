# Trading Valley Strategy Design
###### tags: Python, Machine Learning

#### **2022 Fall/Winter**  *cr: tunyuanchang*

## Dataset
Choose "COCA COLA CO (KO)" as investment target.
The test data is from “2022/01/01” to “2022/09/30”.
The training data includes all data except the test data(from "2016/01/01" to "2021/12/31").
- The initial asset is $100000, all-in on every trade.
- Only considering the long position.
- The fee is ignored.

## Goal
Design a strategy which makes the maximum profit and high sharp ratio.

## Implement
Design a classifier to predict the ups and downs of the stock.
Based on the prediction, adopt the method of high-frequency trading.

## Result
For test data -
獲利(Profit): $27351, 總報酬率(%): 27.351226, 年化報酬率(%): 70.001187, 日平均報酬率(%): 0.145485, Sharpe Ratio: 2.676116
