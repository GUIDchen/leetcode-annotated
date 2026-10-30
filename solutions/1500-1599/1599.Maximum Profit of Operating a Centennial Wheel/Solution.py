# 题目：1599. 经营摩天轮的最大利润（Maximum Profit of Operating a Centennial Wheel）
# 思路：按轮模拟，累计等待人数、每轮最多上 4 人，维护累计利润并在出现更高利润时记录轮数。
# 时间复杂度：O(n)，每轮处理一次到达数据；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minOperationsMaxProfit(  # 返回达到最大利润所需的最少轮数，不盈利返回 -1
        self, customers: List[int], boardingCost: int, runningCost: int  # 三个参数：每轮到达人数、每人票价、每轮运营成本
    ) -> int:  # 返回值类型为 int，即最少轮数
        ans = -1  # 达到最大利润的最少轮数，-1 表示怎么运营都不赚钱
        mx = t = 0  # mx 记录历史最大利润，t 记录当前累计利润
        wait = 0  # 排队等待上车的总人数
        i = 0  # 已经读到的到达轮次
        while wait or i < len(customers):  # 还有人排队或在等后续顾客到达，就继续转
            wait += customers[i] if i < len(customers) else 0  # 本轮新到达的顾客加入等待队列
            up = wait if wait < 4 else 4  # 摩天轮一次最多上 4 人
            wait -= up  # 上车的人从等待队列中移除
            t += up * boardingCost - runningCost  # 本轮收入减去运营成本，累加到总利润
            i += 1  # 转完一轮，轮数加一
            if t > mx:  # 只有出现更高利润才更新答案
                mx = t  # 记录新的最大利润
                ans = i  # 记录达到该利润的最少轮数
        return ans  # 返回最少轮数（从未盈利则为 -1）
