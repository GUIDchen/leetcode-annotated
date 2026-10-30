# 题目：3155. 可升级服务器的最大数量（Maximum Number of Upgradable Servers）
# 核心思路：第 i 类服务器若升级 k 台则卖出 count[i]-k 台，预算约束 money[i]+(count[i]-k)*sell[i] >= k*upgrade[i] 解出 k 的上界，再与 count[i] 取较小值；各类互不影响。
# 时间复杂度：O(n)，n 为服务器种类数，每类只做一次整除；空间复杂度：O(n)，仅答案列表（不计输入）。
class Solution:  # LeetCode 约定的题解类
    def maxUpgrades(  # 开始定义 maxUpgrades，参数较多所以分成多行书写
        self, count: List[int], upgrade: List[int], sell: List[int], money: List[int]  # count：每类数量；upgrade：升级成本；sell：旧机售价；money：可用资金
    ) -> List[int]:  # 返回每类服务器最多可升级的台数列表
        ans = []  # 用来收集每类服务器的答案
        for cnt, cost, income, cash in zip(count, upgrade, sell, money):  # 用 zip 把四个等长数组按类别配对，同时取出这一类的四个量
            ans.append(min(cnt, (cnt * income + cash) // (cost + income)))  # 整除求上界 k=(cnt*income+cash)//(cost+income)，再与总数 cnt 取 min 防止超过现有台数
        return ans  # 返回答案列表
