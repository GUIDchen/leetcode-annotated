# 题目：3103. 查找热门话题标签 II（Find Trending Hashtags II）
# 思路：先筛出 2024 年 2 月的推文，再用正则 r"#\w+" 抽出每条推文里的话题，摊平后计数，最后按次数、话题字典序双降序排序取前 3。
# 时间复杂度：O(N log N)，N 为话题出现总次数（排序主导）；空间复杂度：O(N)，用于存放全部话题。

import pandas as pd  # 导入 pandas，后面用 DataFrame 做日期筛选、正则抽取与计数


def find_trending_hashtags(tweets: pd.DataFrame) -> pd.DataFrame:  # 函数签名：输入推文表，输出热门话题表
    # Filter tweets for February 2024  # 原有注释：只保留 2024 年 2 月的推文
    tweets_feb_2024 = tweets[tweets["tweet_date"].between("2024-02-01", "2024-02-29")]  # 用 between 做闭区间筛选，得到 2 月子表

    # Extract hashtags from tweets  # 原有注释：抽取话题标签
    hashtags = tweets_feb_2024["tweet"].str.findall(r"#\w+")  # 对每条推文用正则找出所有 #话题，结果仍是每行一个列表

    # Flatten list of hashtags  # 原有注释：把嵌套列表摊平
    all_hashtags = [tag for sublist in hashtags for tag in sublist]  # 双层推导式把「列表的列表」压成一个大列表

    # Count occurrences of each hashtag  # 原有注释：统计每个话题出现次数
    hashtag_counts = pd.Series(all_hashtags).value_counts().reset_index()  # value_counts 计数，reset_index 把结果变回普通表
    hashtag_counts.columns = ["hashtag", "count"]  # 把默认列名改成题目要求的 hashtag 与 count

    # Sort by count of hashtag in descending order  # 原有注释：按次数降序排序
    hashtag_counts = hashtag_counts.sort_values(  # 多列排序：先按次数，再按话题名
        by=["count", "hashtag"], ascending=[False, False]  # 两列都降序，次数相同时话题字典序较大的排前面
    )  # 排序调用结束

    # Get top 3 trending hashtags  # 原有注释：取前 3 名
    top_3_hashtags = hashtag_counts.head(3)  # head(3) 取排序后的前三行

    return top_3_hashtags  # 返回 Top3 结果表
