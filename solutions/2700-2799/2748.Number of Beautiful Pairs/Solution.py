# 题目：2748. 美丽下标对的数目（Number of Beautiful Pairs）
# 思路：顺序扫描，用 cnt[d] 记录已出现元素中最高位为 d 的个数；处理当前元素时枚举 d，统计 gcd(d, 当前末位) == 1 的前驱数量。
# 时间复杂度：O(n * 10)，每个元素常数次枚举；空间复杂度：O(10)，只有长度为 10 的计数数组。
class Solution:  # LeetCode 约定的题解类
    def countBeautifulPairs(self, nums: List[int]) -> int:  # nums：输入数组；返回美丽下标对的数目
        cnt = [0] * 10  # cnt[d]：已扫描过的元素中最高位为 d 的个数
        ans = 0  # 累加美丽下标对数量
        for x in nums:  # 依次把每个元素当作下标对中的后者 j
            for y in range(10):  # 枚举前面元素可能的首位数字 y
                if cnt[y] and gcd(x % 10, y) == 1:  # 存在首位为 y 的前驱且 gcd(前驱首位, 当前末位) == 1 时配对合法
                    ans += cnt[y]  # 这些前驱都能与当前元素组成美丽下标对
            cnt[int(str(x)[0])] += 1  # 把当前元素转成字符串取首位，计入计数供后续元素使用
        return ans  # 返回美丽下标对总数
