# Academic-Project-on-the-Impact-of-Earning-Report-based-on-object-oriented-programming-in-Cpp
## Chose 498 S&amp;P 500 component stocks and categorized them according to the spread between their estimated and actual EPS, then calculated abnormal average returns of each group and plotted their graph individually by establishing a user-friendly menu

# The aim of this project is to evaluate the impact of earning report on stock price. Specifically, we choose 498 S&P 500 component stocks from Bloomberg and divide the stock into three groups according to the spread between their estimated EPS and actual performance, then we use C++ to download their daily prices, calculate and output graphs of the Abnormal Average Returns (AAR) and Cumulative Abnormal Average Returns (CAAR) of each groups then we use Gnuplot to draw the CAAR plot.

# Data Processing
1. Download estimated EPS, actual EPS and component stock of S&P 500 from Bloomberg. 
2. Fetch the data by using <Extract.h> the date range is from  2017-3-31 to 2017-11-30.
3. Divide data separately according to the tickers
4. Classify the data into three groups including “Beat”(difference is over 5%) “Meet” (less than 3%)and “Miss”( in between).
5. Standardize the date from raw date(from  2017-3-31 to 2017-11-30) into 61 days.
6. Randomly select 40 stocks from each group

