# Code
## How to run code
### Open in **Google Colab**
### Requirement for packages: 
- yfinance
- scikit-learn
- Matplotlib
- requests
- pandas
- json
- numpy

# Report
## Characteristics in report
- Part I: Design a strategy which makes the maximum profit and high sharp ratio.
Use Machine learning to classify the rise or fall in the stock price.
Use Support Vector Classification for the classifier model.
Input: sybol rating of trend for 3 days and VIX
Output: True for rise & False for fall
Take COCA COLA CO as the dataset.
Train 2016-01-01 ~ 2021-12-31
Test 2022-01-01 ~ 2022-09-30
- Part II: What's your strategy to decide the entry and the exit?
Trading frequency: buy and sell in one day. (Since ignore any fee and all-in in one trade, use high-frequency trading)
With the classifier model, if the prediction is rise, buy at open and sell at close in one day. Otherwise, do nothing.
- Part III:	How's your strategy's performance? Including profit, sharp ratio and asset change chart.
For test data -
獲利(Profit): $27351
總報酬率(%): 27.351226
年化報酬率(%): 70.001187
日平均報酬率(%): 0.145485
Sharpe Ratio: 2.676116
Asset change chart: as the picture show in report