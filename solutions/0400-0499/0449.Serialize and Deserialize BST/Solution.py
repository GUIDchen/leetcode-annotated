# 题目：449. 序列化和反序列化二叉搜索树（Serialize and Deserialize BST）
# 思路：先序遍历序列加上 BST 的值域约束就能唯一还原——serialize 输出先序值串，deserialize 用开区间 (mi, mx) 逐个认领结点。
# 时间复杂度：O(n)，序列化遍历一次、反序列化每个值只消费一次；空间复杂度：O(n)，值列表与递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Codec:  # 序列化 / 反序列化二叉搜索树的编解码器
    def serialize(self, root: Optional[TreeNode]) -> str:  # root：待序列化的 BST 根结点；返回空格分隔的先序遍历值串
        """Encodes a tree to a single string."""

        def dfs(root: Optional[TreeNode]):  # 内层递归函数：按先序把结点值逐个追加进 nums
            if root is None:  # 递归出口：空结点
                return  # 什么都不写，直接返回
            nums.append(root.val)  # 先访问根：记录根结点的值
            dfs(root.left)  # 再递归左子树
            dfs(root.right)  # 最后递归右子树

        nums = []  # 保存先序遍历得到的结点值，dfs 闭包会往这里追加
        dfs(root)  # 从根结点开始遍历，把整棵树写进 nums
        return " ".join(map(str, nums))  # 转成空格分隔的字符串作为编码结果

    def deserialize(self, data: str) -> Optional[TreeNode]:  # data：serialize 的输出；返回还原后的 BST 根结点
        """Decodes your encoded data to tree."""

        def dfs(mi: int, mx: int) -> Optional[TreeNode]:  # 内层递归函数：用开区间 (mi, mx) 判断当前值是否属于该子树
            nonlocal i  # 声明要修改外层的读取下标 i（不是新建局部变量）
            if i == len(nums) or not mi <= nums[i] <= mx:  # 序列已读完，或当前值不在允许值域内，说明该子树为空
                return None  # 该位置没有结点
            x = nums[i]  # 取出当前值：它必然是这一子树的根
            root = TreeNode(x)  # 用该值新建结点
            i += 1  # 下标后移，下一次递归处理后面的值
            root.left = dfs(mi, x)  # 左子树的值都必须小于 x，值域收紧为 (mi, x)
            root.right = dfs(x, mx)  # 右子树的值都必须大于 x，值域收紧为 (x, mx)
            return root  # 返回还原好的子树根

        nums = list(map(int, data.split()))  # 按空白切成整数序列，顺序就是先序遍历
        i = 0  # 先序序列的读取下标
        return dfs(-inf, inf)  # 整棵树的值域是全体整数，用正负无穷作开区间边界


# Your Codec object will be instantiated and called as such:
# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# tree = ser.serialize(root)
# ans = deser.deserialize(tree)
# return ans
