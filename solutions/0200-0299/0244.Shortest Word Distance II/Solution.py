# 题目：244. 最短单词距离 II（Shortest Word Distance II）
# 思路：构造时建立「单词 → 全部下标」的索引；查询时对两个有序下标列表做双指针归并，每步比较后移动较小的一侧。
# 时间复杂度：构造 O(n)，每次查询 O(a + b)（a、b 为两词出现次数）；空间复杂度：O(n)，存下所有单词的下标。
class WordDistance:  # 预处理单词列表，支持多次最短距离查询
    def __init__(self, wordsDict: List[str]):  # 构造函数：建立「单词 → 出现的所有下标」索引
        self.d = defaultdict(list)  # 默认值字典：访问不存在的键时自动创建空列表
        for i, w in enumerate(wordsDict):  # 遍历整个单词列表
            self.d[w].append(i)  # 把当前下标追加到该单词对应的列表

    def shortest(self, word1: str, word2: str) -> int:  # 查询两个单词的最短距离
        a, b = self.d[word1], self.d[word2]  # 取出两个单词各自的下标列表
        ans = inf  # 最小距离，先置为正无穷
        i = j = 0  # 两个有序下标列表的游标
        while i < len(a) and j < len(b):  # 双指针归并式扫描，两个列表都还没走完
            ans = min(ans, abs(a[i] - b[j]))  # 用当前这一对下标差更新最小距离
            if a[i] <= b[j]:  # 下标较小的一侧后移，才可能找到更近的一对
                i += 1  # 左列表游标右移
            else:  # 否则说明右列表下标更小
                j += 1  # 右列表游标右移
        return ans  # 返回最小距离


# Your WordDistance object will be instantiated and called as such:
# obj = WordDistance(wordsDict)
# param_1 = obj.shortest(word1,word2)
