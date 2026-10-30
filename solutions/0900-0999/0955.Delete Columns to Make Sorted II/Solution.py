# 题目：955. 删列造序 II（Delete Columns to Make Sorted II）
# 思路：逐列贪心，用布尔列表记录哪些相邻行已由更靠左的列确定严格递增；若当前列让尚未确定的行出现逆序就整列删除。
# 时间复杂度：O(n·m)，每列最多扫描 n-1 对相邻行；空间复杂度：O(n)，状态列表长度为 n-1。
class Solution:  # LeetCode 约定的题解类
    def minDeletionSize(self, strs: List[str]) -> int:  # strs 是等长字符串列表，返回最少要删除的列数
        n = len(strs)  # n：字符串个数（行数）
        m = len(strs[0])  # m：每个字符串的长度（列数）
        st = [False] * (n - 1)  # st[i] 为 True 表示第 i 行与第 i+1 行的顺序已确定，后续列不必再比较
        ans = 0  # ans：累计删除的列数
        for j in range(m):  # 按列从左到右处理
            must_del = False  # 当前这一列是否必须删除
            for i in range(n - 1):  # 检查所有还没分出顺序的相邻行
                if not st[i] and strs[i][j] > strs[i + 1][j]:  # 本列出现逆序，该列必须删除
                    must_del = True  # 标记必须删除
                    break  # 已经确定要删，不必再看后面的行
            if must_del:  # 本列必须删，删除列数加一
                ans += 1  # 本列保留，用它来确定部分相邻行的严格顺序
            else:  # 再扫一遍，看哪些相邻行在本列能分出大小
                for i in range(n - 1):  # 上面小于下面，说明这两行已严格递增
                    if not st[i] and strs[i][j] < strs[i + 1][j]:  # 标记为已确定，之后不再检查这一对
                        st[i] = True
        return ans  # 返回最少删除列数
