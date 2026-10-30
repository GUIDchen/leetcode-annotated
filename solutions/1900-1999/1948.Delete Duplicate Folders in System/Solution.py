# 题目：1948. 删除系统中的重复文件夹（Delete Duplicate Folders in System）
# 思路：用 Trie 建目录树，自底向上为每棵子树生成结构签名，签名重复的整棵子树标记删除，最后 DFS 输出剩余路径。
# 时间复杂度：O(N·L·logN)，签名需要排序；空间复杂度：O(N·L)，Trie 节点与签名哈希表。
class Trie:  # 目录树节点
    def __init__(self):  # 初始化一个目录节点
        self.children: Dict[str, "Trie"] = defaultdict(Trie)  # 子目录名 → 子节点，缺省时自动新建
        self.deleted: bool = False  # 该子树是否因为重复而需要被删除


class Solution:  # LeetCode 约定的题解类
    def deleteDuplicateFolder(self, paths: List[List[str]]) -> List[List[str]]:  # paths：若干条目录路径
        root = Trie()  # 虚拟根节点，便于统一处理各条路径
        for path in paths:  # 逐条路径插入 Trie
            cur = root  # 每条路径都从根节点开始走
            for name in path:  # 沿路径逐个目录名向下
                if cur.children[name] is None:  # 该子目录还不存在
                    cur.children[name] = Trie()  # 新建节点挂到父节点下
                cur = cur.children[name]  # 走到这个子目录，继续处理下一个名字

        g: Dict[str, Trie] = {}  # 结构签名 → 第一次出现该签名的节点

        def dfs(node: Trie) -> str:  # 递归求以 node 为根的子树签名
            if not node.children:  # 叶子目录没有子结构
                return ""  # 签名为空串
            subs: List[str] = []  # 收集每个子目录的「名字(子签名)」
            for name, child in node.children.items():  # 遍历所有子目录
                subs.append(f"{name}({dfs(child)})")  # 先递归求子签名，再拼成字符串
            s = "".join(sorted(subs))  # 排序后拼接，消除子目录顺序带来的差异
            if s in g:  # 之前已经出现过完全相同的结构
                node.deleted = g[s].deleted = True  # 当前子树与先前那棵都标记为待删除
            else:
                g[s] = node  # 首次出现该签名，登记下来供后续比较
            return s  # 把签名交回父节点继续拼接

        def dfs2(node: Trie) -> None:  # 第二次 DFS，收集保留下来的路径
            if node.deleted:  # 被标记删除的子树
                return  # 整棵直接跳过，不输出任何路径
            if path:  # 根节点本身不算一条目录路径
                ans.append(path[:])  # 把当前路径的副本加入答案
            for name, child in node.children.items():  # 递归处理每个子目录
                path.append(name)  # 先压入子目录名
                dfs2(child)  # 递归进入该子目录
                path.pop()  # 回溯：弹出子目录名，恢复现场

        dfs(root)  # 自底向上算出所有签名并标记重复子树
        ans: List[List[str]] = []  # 存放所有被保留下来的目录路径
        path: List[str] = []  # 回溯过程中维护的当前路径
        dfs2(root)  # 从根节点开始收集答案
        return ans  # 返回所有保留下来的目录路径
