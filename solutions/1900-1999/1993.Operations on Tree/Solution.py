# 题目：1993. 树上的操作（Operations on Tree）
# 思路：用 self.locked 记录每个节点的持锁人，用父数组向上回溯、用儿子表向下 DFS。lock/unlock 一次判断即可，upgrade 先查祖先全未锁，再 DFS 清空后代的锁。
# 时间复杂度：lock/unlock 为 O(1)，构造为 O(n)，upgrade 最坏为 O(n)；空间复杂度：O(n) 存父数组、锁状态与儿子表。
class LockingTree:  # 关键：维护「每个节点被谁锁住」以及树的两个方向（父亲、儿子）
    def __init__(self, parent: List[int]):  # parent[i] 是节点 i 的父节点，根节点 0 的父节点为 -1
        n = len(parent)  # 节点个数
        self.locked = [-1] * n  # self.locked[i] 记录节点 i 的持锁人，-1 表示未上锁
        self.parent = parent  # 保存父数组，供 upgrade 向上回溯
        self.children = [[] for _ in range(n)]  # 邻接表：self.children[i] 存放节点 i 的全部儿子
        for son, fa in enumerate(parent[1:], 1):  # son 从 1 开始（根节点没有父亲），fa 是它的父节点
            self.children[fa].append(son)  # 建立向下的边，后面 upgrade 才能 DFS 后代

    def lock(self, num: int, user: int) -> bool:  # lock：给节点 num 上锁，user 是请求者编号
        if self.locked[num] == -1:  # -1 表示当前没有锁，可以上锁
            self.locked[num] = user  # 记录锁的持有者
            return True  # 上锁成功
        return False  # 已经被别人锁住，上锁失败

    def unlock(self, num: int, user: int) -> bool:  # unlock：只有请求者正是持锁人时才允许解锁
        if self.locked[num] == user:  # 持锁人与请求者一致
            self.locked[num] = -1  # 置回 -1，恢复未上锁状态
            return True  # 解锁成功
        return False  # 不是持锁人（或本来就没锁），解锁失败

    def upgrade(self, num: int, user: int) -> bool:  # upgrade：要求祖先全部未锁、后代至少有一把锁，然后把后代的锁全部清掉并锁住 num
        def dfs(x: int):  # 内部函数：深度优先清除 x 的后代锁，并顺带记录是否存在已锁后代
            nonlocal find  # 声明 find 来自外层函数，这里需要修改它
            for y in self.children[x]:  # 逐个访问儿子
                if self.locked[y] != -1:  # 儿子当前被锁住
                    self.locked[y] = -1  # 顺手清掉这个儿子的锁
                    find = True  # 记录确实存在已锁后代
                dfs(y)  # 递归处理更深的后代

        x = num  # 从 num 出发向上回溯
        while x != -1:  # 根节点的父节点是 -1，走到 -1 说明祖先检查完毕
            if self.locked[x] != -1:  # 任一祖先已被锁住
                return False  # 不满足「祖先全未锁」，升级失败
            x = self.parent[x]  # 继续向父节点回溯

        find = False  # find 标记后代中是否至少有一把锁
        dfs(num)  # 从 num 开始收集并清除后代的锁
        if not find:  # 一个已锁后代都没有
            return False  # 不满足升级条件，失败
        self.locked[num] = user  # 条件全部满足，给 num 上锁，持锁人为 user
        return True  # 升级成功


# 下面是 LeetCode 判题器给出的调用示例（保持原样）
# Your LockingTree object will be instantiated and called as such:
# obj = LockingTree(parent)
# param_1 = obj.lock(num,user)
# param_2 = obj.unlock(num,user)
# param_3 = obj.upgrade(num,user)
