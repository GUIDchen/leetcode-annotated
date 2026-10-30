# 题目：1169. 查询无效交易（Invalid Transactions）
# 思路：按姓名分组记录每条交易的 (时间, 城市, 下标)，逐条与该姓名已有交易比较：金额 > 1000 或 60 分钟内跨城市交易都算无效。
# 时间复杂度：O(n^2)，最坏情况同名交易两两比较；空间复杂度：O(n)，分组字典与无效下标集合都是线性规模。
class Solution:  # 题解类
    def invalidTransactions(self, transactions: List[str]) -> List[str]:  # 找出所有无效交易并按原字符串返回
        d = defaultdict(list)  # 按姓名分组，值是 (时间, 城市, 下标) 的列表
        idx = set()  # 无效交易的下标集合，用集合天然去重
        for i, x in enumerate(transactions):  # 逐条处理，i 是下标，x 是交易字符串
            name, time, amount, city = x.split(",")  # 按逗号切出姓名、时间、金额、城市
            time, amount = int(time), int(amount)  # 把字符串形式的时间和金额转成整数
            d[name].append((time, city, i))  # 把本条交易加入该姓名的列表，供后续比较
            if amount > 1000:  # 金额超过 1000 的交易无效
                idx.add(i)  # 标记为无效
            for t, c, j in d[name]:  # 与该姓名已记录的所有交易逐一比较
                if c != city and abs(time - t) <= 60:  # 城市不同且时间差不超过 60 分钟即为无效
                    idx.add(i)  # 当前交易标记为无效
                    idx.add(j)  # 与之冲突的另一条交易也无效
        return [transactions[i] for i in idx]  # 按下标取出原始字符串，组成答案
