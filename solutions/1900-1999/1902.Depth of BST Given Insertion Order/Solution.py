# 题目：1902. 给定二叉搜索树的插入顺序求深度（Depth of BST Given Insertion Order）🔒
# 思路：按插入顺序建树。新节点一定挂在有序键中它的前驱或后继下面，深度 = 1 + max(前驱深度, 后继深度)，用有序字典维护「键 → 深度」并随时更新最大值。
# 时间复杂度：O(n log n)，每次查询前驱/后继与插入都是 O(log n)；空间复杂度：O(n)，有序字典保存 n 个键。
class Solution:  # LeetCode 约定的题解类
    def maxDepthBST(self, order: List[int]) -> int:  # order：节点值按插入顺序排列的数组
        sd = SortedDict({0: 0, inf: 0, order[0]: 1})  # 有序映射「键 → 深度」；哨兵 0 与 inf 的深度为 0，避免查询前驱/后继时越界；第一个节点深度为 1
        ans = 1  # 记录整棵 BST 的最大深度，最初只有根节点
        for v in order[1:]:  # 按插入顺序处理除根节点外的每个节点
            lower = sd.bisect_left(v) - 1  # bisect_left 返回第一处 >= v 的位置，减 1 即前驱（小于 v 的最大键）的下标
            higher = lower + 1  # 后继（大于 v 的最小键）在有序序列中紧挨着前驱
            depth = 1 + max(sd.values()[lower], sd.values()[higher])  # 新节点挂在更深的一侧下面，所以深度 = 1 + 前驱与后继深度的较大值
            ans = max(ans, depth)  # 用新节点的深度更新全局最大深度
            sd[v] = depth  # 把新节点及其深度写入有序映射，供后续节点查找前驱/后继
        return ans  # 最大深度就是整棵 BST 的深度
