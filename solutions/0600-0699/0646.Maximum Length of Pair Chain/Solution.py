# 题目：646. 最长数对链（Maximum Length of Pair Chain）
# 思路：按右端点升序排序后贪心扫描，只要当前数对的左端点严格大于已选链的右端点就把它接入链尾，这样给后面留出的空间最大。
# 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(1)，只用到常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def findLongestChain(self, pairs: List[List[int]]) -> int:  # pairs 是输入的数对数组，返回最长数对链长度
        pairs.sort(key=lambda x: x[1])  # 关键一步：按右端点 x[1] 升序排序，为贪心做准备
        ans, pre = 0, -inf  # ans 记录链长；pre 记录链尾右端点，用负无穷表示尚未选数对
        for a, b in pairs:  # 按右端点从小到大依次拆包出左端点 a 与右端点 b
            if pre < a:  # 左端点严格大于链尾右端点，当前数对可以接上
                ans += 1  # 链长加一
                pre = b  # 链尾右端点更新为当前数对右端点
        return ans  # 返回最长数对链长度
