# 题目：1791. 找出星型图的中心节点（Find Center of Star Graph）
# 思路：中心点与其余所有点相连，必然同时出现在前两条边中；判断第一条边的第一个端点是否也属于第二条边即可。
# 时间复杂度：O(1)，只检查两条边；空间复杂度：O(1)，只用常数空间。
class Solution:  # LeetCode 约定的题解类
    def findCenter(self, edges: List[List[int]]) -> int:  # 返回星型图的中心节点编号
        return edges[0][0] if edges[0][0] in edges[1] else edges[0][1]  # 若 edges[0][0] 也出现在第二条边中，它就是中心；否则第一条边的另一个端点 edges[0][1] 是中心
