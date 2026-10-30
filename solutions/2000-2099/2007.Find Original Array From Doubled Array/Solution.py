# 题目：2007. 从双倍数组中还原原数组（Find Original Array From Doubled Array）
# 思路：升序排序后最小值一定属于原数组，于是用计数器从小到大贪心配对：取出 x 放进答案并消耗一个 x 和一个 2x；任何一步配对失败就返回空数组。
# 时间复杂度：O(n log n)，排序占主导，贪心扫描是 O(n)；空间复杂度：O(n)，计数器存不同值。
class Solution:  # LeetCode 约定的题解类
    def findOriginalArray(self, changed: List[int]) -> List[int]:  # changed 是双倍数组；返回还原出的原数组，无法还原时返回空列表
        changed.sort()  # 升序排序：排序后最小值必然属于原数组
        cnt = Counter(changed)  # 统计每个值的剩余个数；Counter 访问不存在的键会返回 0，不会报错
        ans = []  # ans 收集原数组的元素
        for x in changed:  # 按升序遍历，保证先处理较小的值
            if cnt[x] == 0:  # 该值已经被前面的元素配对消耗完
                continue  # 这一份已经用掉，跳过
            cnt[x] -= 1  # 把 x 分配给原数组，剩余个数减一
            if cnt[x << 1] <= 0:  # 与 x 配对的元素应当是 2x，若它已经没有剩余则无法配对
                return []  # 无法还原，返回空列表
            cnt[x << 1] -= 1  # 配对成功，2x 的剩余个数也减一
            ans.append(x)  # x 属于原数组，收集起来
        return ans  # 全部元素都配对成功，返回原数组
