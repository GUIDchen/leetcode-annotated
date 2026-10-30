# 题目：406. 根据身高重建队列（Queue Reconstruction by Height）
# 思路：先按身高 h 降序、同高按 k 升序排序，再逐个把 [h, k] 插入到下标 k 处。
# 时间复杂度：O(n^2)，排序 O(n log n) 加 n 次列表中间插入；空间复杂度：O(n)，答案列表存 n 个人。
class Solution:  # LeetCode 约定的题解类
    def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:  # people 每项是 [h, k]：身高 h 与前面身高不低于 h 的人数 k
        people.sort(key=lambda x: (-x[0], x[1]))  # 关键排序：h 降序（-x[0]），h 相同则 k 升序
        ans = []  # 结果队列，下标即 k（它前面的人数）
        for p in people:  # 按身高从高到低处理
            ans.insert(p[1], p)  # 比 p 高的人已经就位，插到下标 p[1] 处正好满足它的 k
        return ans  # 返回重建后的队列
