# 题目：3087. 查找热门话题标签（Find Trending Hashtags，会员题）
# 思路：先筛出 2024 年 2 月的推文，用正则抽出每条推文的话题标签，再按出现次数与标签名倒序排序取前三。
# 时间复杂度：O(n log n)，n 为推文条数，瓶颈在排序；空间复杂度：O(n)，用于存放去重后的标签计数。
import pandas as pd  # 导入 pandas，LeetCode 的 DataFrame 题目环境已提供该库


def find_trending_hashtags(tweets: pd.DataFrame) -> pd.DataFrame:  # tweets 为推文表，返回 2024 年 2 月出现次数最多的 3 个话题标签
    tweets = tweets[tweets["tweet_date"].dt.strftime("%Y%m") == "202402"]  # 只保留 tweet_date 格式化后为 202402 的推文，即 2024 年 2 月
    tweets["hashtag"] = "#" + tweets["tweet"].str.extract(r"#(\w+)")  # 用正则从推文内容里抓出第一个 # 后面的标签名，再补回 # 号
    hashtag_counts = tweets["hashtag"].value_counts().reset_index()  # 统计每个标签的出现次数，reset_index 把索引还原成普通列
    hashtag_counts.columns = ["hashtag", "hashtag_count"]  # 把结果两列命名为 hashtag 与 hashtag_count，符合题目输出格式
    hashtag_counts = hashtag_counts.sort_values(  # 按次数降序、标签名降序排序（次数相同则字符串更大的在前）
        by=["hashtag_count", "hashtag"], ascending=[False, False]  # 排序键：先比次数、再比标签名，ascending 中的 False 表示降序
    )  # 多行调用收尾
    top_3_hashtags = hashtag_counts.head(3)  # 取排序后的前 3 行，即最热门的 3 个标签
    return top_3_hashtags  # 按题目要求返回前 3 名标签及其出现次数
