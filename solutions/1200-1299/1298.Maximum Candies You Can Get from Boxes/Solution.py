# 题目：1298. 你能从盒子里获得的最大糖果数（Maximum Candies You Can Get from Boxes）
# 思路：BFS。has 记录已经到手的盒子，took 记录已经开过并计过糖果的盒子；队列里只放已打开的盒子。
# 时间复杂度：O(n + 钥匙总数 + 盒中盒总数)；空间复杂度：O(n)，两个集合加一个队列。
class Solution:  # LeetCode 约定的题解类
    def maxCandies(  # 返回能获得的最大糖果数
        self,  # 实例方法的固定参数
        status: List[int],  # status[i]：第 i 个盒子是否已经打开
        candies: List[int],  # candies[i]：第 i 个盒子里的糖果数
        keys: List[List[int]],  # keys[i]：第 i 个盒子里的钥匙能打开的盒子编号
        containedBoxes: List[List[int]],  # containedBoxes[i]：第 i 个盒子里装的盒子编号
        initialBoxes: List[int],  # initialBoxes：一开始就拥有的盒子编号
    ) -> int:  # 返回值为糖果总数
        q = deque()  # 待处理的「已打开」盒子
        has, took = set(initialBoxes), set()  # has：已经到手的盒子；took：已经开过并计过糖果的盒子
        ans = 0  # 已获得的糖果总数

        for box in initialBoxes:  # 先遍历初始拥有的盒子
            if status[box]:  # 初始就是打开的盒子
                q.append(box)  # 放进队列等待处理
                took.add(box)  # 标记为已打开，避免重复计分
                ans += candies[box]  # 拿走盒中糖果
        while q:  # 队列非空说明还有能打开的盒子
            box = q.popleft()  # 取出队首盒子
            for k in keys[box]:  # 处理该盒子里的所有钥匙
                if not status[k]:  # 钥匙对应的盒子之前是锁着的
                    status[k] = 1  # 用钥匙把它打开
                    if k in has and k not in took:  # 该盒子已到手且还没开过
                        q.append(k)  # 可以立即打开，入队
                        took.add(k)  # 标记为已打开
                        ans += candies[k]  # 拿走糖果

            for b in containedBoxes[box]:  # 处理这个盒子里装的所有盒子
                has.add(b)  # 盒中盒到手
                if status[b] and b not in took:  # 已经能用钥匙打开且还没处理过
                    q.append(b)  # 入队
                    took.add(b)  # 标记为已打开
                    ans += candies[b]  # 拿走糖果
        return ans  # 返回累计获得的糖果数
