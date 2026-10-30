# 题目：2537. 统计好子数组的数目（Count the Number of Good Subarrays）
# 思路：滑动窗口。cur 记录窗口内同值元素的配对对数，右端每右移一次就把左端缩到不能再缩为止，
# 时间 O(n)，空间 O(n)（Counter 最多存不同元素个数）。
class Solution:  # LeetCode 约定的题解类
    def countGood(self, nums: List[int], k: int) -> int:  # nums 为数组，k 为好子数组所需的配对对数
        cnt = Counter()  # Counter 记录窗口内每个值的出现次数，不存在的键取值为 0
        ans = cur = 0  # ans 存答案，cur 存当前窗口内的配对对数
        i = 0  # 窗口左端点
        for x in nums:  # 右端点不断右移，逐个把元素纳入窗口
            cur += cnt[x]  # x 与窗口内已有的 cnt[x] 个相同元素各配一对，先累加配对增量
            cnt[x] += 1  # 再把 x 的计数加一（顺序不能反过来，否则会多算）
            while cur - cnt[nums[i]] + 1 >= k:  # 若移走最左元素后配对数仍不少于 k，说明窗口还能继续缩
                cnt[nums[i]] -= 1  # 把最左元素的计数减一
                cur -= cnt[nums[i]]  # cur 减去该值减少后的个数，即因移除它而消失的配对数
                i += 1  # 左端点右移
            if cur >= k:  # 此时窗口内配对对数已达 k，窗口合法
                ans += i + 1  # 起点可取 0..i 中任一位置，终点是当前右端，共 i+1 个好子数组
        return ans  # 返回好子数组总数
