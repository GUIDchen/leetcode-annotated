# 题目：1600. 王位继承顺序（Throne Inheritance）
# 思路：把继承关系建成多叉树，用邻接表存孩子、用集合标记死亡，查询时从国王做一次前序遍历。
# 时间复杂度：birth/death O(1)，getInheritanceOrder O(n)；空间复杂度：O(n)，存下整棵树与结果。
class ThroneInheritance:  # 题目要求的王位继承类，需要支持出生、死亡与查询继承顺序

    # 初始化：记录国王，并建好死亡集合与父亲到孩子的邻接表
    def __init__(self, kingName: str):  # 构造函数：kingName 为国王姓名
        self.king = kingName  # 保存根节点，后续 DFS 从国王开始
        self.dead = set()  # 已死亡成员集合，查询时跳过
        self.g = defaultdict(list)  # 邻接表：父亲 → 孩子列表，缺失的键自动建空列表

    # 记录一次出生：childName 的父亲是 parentName
    def birth(self, parentName: str, childName: str) -> None:  # 出生事件
        self.g[parentName].append(childName)  # 追加到父亲的孩子列表末尾，从而保持出生顺序

    # 记录一次死亡：只做标记不删节点，保证其他成员在树中的位置不变
    def death(self, name: str) -> None:  # 死亡事件
        self.dead.add(name)  # 放入死亡集合，DFS 输出时跳过

    # 返回当前所有在世者的继承顺序（多叉树的前序遍历）
    def getInheritanceOrder(self) -> List[str]:  # 查询继承顺序
        def dfs(x: str):  # 内层前序遍历：先访问自己，再按出生顺序访问孩子
            x not in self.dead and ans.append(x)  # 利用 and 的短路特性：在世才把姓名加入结果
            for y in self.g[x]:  # 按出生顺序遍历所有孩子
                dfs(y)  # 递归处理孩子及其后代

        # 每次查询都重新遍历，ans 作为闭包变量被内层函数写入
        ans = []  # 保存本次查询的遍历结果
        dfs(self.king)  # 从国王开始做前序遍历
        return ans  # 返回收集到的顺序


# Your ThroneInheritance object will be instantiated and called as such:
# obj = ThroneInheritance(kingName)
# obj.birth(parentName,childName)
# obj.death(name)
# param_3 = obj.getInheritanceOrder()
