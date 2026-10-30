# 题目：428. 序列化和反序列化 N 叉树（Serialize and Deserialize N-ary Tree）
# 思路：序列化用 BFS，先写根节点值，再对每个节点输出全部子节点的值并以 # 收尾；反序列化按同样的 BFS 顺序把值读回成子节点。
# 时间复杂度：O(n)，每个节点只处理一次；空间复杂度：O(n)，队列与编码串都要存下所有节点。
# 说明：下面是题目自带的 N 叉树 Node 定义（注释块，由判题器提供），仅作参考。
"""
# Definition for a Node.
class Node(object):
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children
"""


class Codec:  # 编解码类
    def serialize(self, root: 'Node') -> str:  # 把 N 叉树编码成逗号分隔的字符串
        if root is None:  # 空树
            return ''  # 用空串表示空树
        ans = [str(root.val)]  # 根节点的值单独写在整个串的最前面
        q = deque([root])  # BFS 队列，初始只有根节点
        while q:  # 队列非空就继续处理
            node = q.popleft()  # 取出队首节点
            for child in node.children or []:  # 依次遍历它的子节点（None 当作空列表处理）
                ans.append(str(child.val))  # 记录子节点的值
                q.append(child)  # 子节点入队，之后还要输出它们的子节点
            ans.append('#')  # 追加一个 # 号，表示当前节点的子节点列表到此结束
        return ','.join(ans)  # 用逗号把全部片段拼成最终字符串

    def deserialize(self, data: str) -> 'Node':  # 把字符串还原成 N 叉树
        if not data:  # 空串表示空树
            return None  # 返回 None
        vals = data.split(',')  # 按逗号切成片段列表
        root = Node(int(vals[0]), [])  # 第一个片段是根节点的值
        q = deque([root])  # BFS 队列，从根节点开始
        i = 1  # 下一个待读取片段的下标
        while q:  # 队列非空说明还有节点需要挂子节点
            node = q.popleft()  # 取出待处理的节点
            while vals[i] != '#':  # 一直读子节点，直到遇到 # 结束标记
                child = Node(int(vals[i]), [])  # 用片段里的值创建子节点
                node.children.append(child)  # 挂到当前节点的子节点列表
                q.append(child)  # 子节点入队，稍后为它读自己的子节点
                i += 1  # 下标后移，准备读下一个片段
            i += 1  # 跳过 # 结束标记
        return root  # 还原完成，返回根节点


# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.deserialize(codec.serialize(root))
