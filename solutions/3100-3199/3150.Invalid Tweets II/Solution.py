# 题目：3150. 无效的推文 II（Invalid Tweets II）
# 思路：用 pandas 的字符串方法对 content 列做三个条件筛选（长度、@ 个数、# 个数），取或后按 tweet_id 排序并投影。
# 时间复杂度：O(n)，每个字符串只扫描常数次；空间复杂度：O(n)，需要一个布尔掩码和筛出的子表。
import pandas as pd  # 引入 pandas，用 DataFrame 完成筛选与排序


def find_invalid_tweets(tweets: pd.DataFrame) -> pd.DataFrame:  # tweets 是推文表，返回无效推文的 tweet_id 列
    invalid_tweets = tweets[  # 开始按条件过滤行
        (tweets["content"].str.len() > 140)  # 条件一：content 长度超过 140
        | (tweets["content"].str.count("@") > 3)  # 条件二：@ 出现次数超过 3；| 表示逻辑或
        | (tweets["content"].str.count("#") > 3)  # 条件三：# 出现次数超过 3；三个条件满足其一即为无效推文
    ].sort_values(by="tweet_id")  # 结果按 tweet_id 升序排列
    return invalid_tweets[["tweet_id"]]  # 只保留 tweet_id 一列返回
