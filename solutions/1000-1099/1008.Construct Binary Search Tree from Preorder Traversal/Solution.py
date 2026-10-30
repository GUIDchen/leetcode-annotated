# 题目：1008. 前序遍历构造二叉搜索树（Construct Binary Search Tree from Preorder Traversal）
# 核心思路：前序首元素是根，二分找出左右子树分界后递归建树
# 复杂度：时间 O(n log n)，每个节点内层二分；空间 O(h)，递归栈深不超过树高
class Solution:  # LeetCode 约定的题解类
    def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:  # preorder：二叉搜索树的前序遍历序列
        def dfs(i: int, j: int) -> Optional[TreeNode]:  # 内层函数：用 preorder[i..j] 构造子树并返回其根
            if i > j:  # 区间为空，说明没有节点
                return None  # 空子树返回 None
            root = TreeNode(preorder[i])  # 前序遍历首元素就是本子树的根
            l, r = i + 1, j + 1  # 在 [i+1, j] 里二分查找第一个大于根值的位置
            while l < r:  # 二分进行中
                mid = (l + r) >> 1  # 取中点，右移一位等价于除以 2 向下取整
                if preorder[mid] > preorder[i]:  # 该元素比根大，属于右子树
                    r = mid  # 右子树起点不晚于 mid，收缩右边界
                else:  # 该元素比根小，属于左子树
                    l = mid + 1  # 左子树至少包含到 mid，收缩左边界
            root.left = dfs(i + 1, l - 1)  # 左子树占据 [i+1, l-1]
            root.right = dfs(l, j)  # 右子树占据 [l, j]
            return root  # 返回构造好的子树根

        return dfs(0, len(preorder) - 1)  # 从整个前序区间 [0, n-1] 开始递归建树
