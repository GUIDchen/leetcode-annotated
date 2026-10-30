# 题目：3208. 交替组 II（Alternating Groups II）
# 思路：把环形数组首尾相接扫两圈，用 cnt 维护当前「相邻两数交替」的连续段长度；进入第二圈后，cnt ≥ k 就说明出现了一个长度为 k 的交替组，计数即可。
# 时间复杂度：O(n)，只扫 2n 个位置；空间复杂度：O(1)，仅用常数个变量。
class Solution:  # LeetCode 题解类，固定入口名
    def numberOfAlternatingGroups(self, colors: List[int], k: int) -> int:  # 统计长度为 k 的交替组个数；colors 为环形颜色数组，k 为组长度
        n = len(colors)  # 环形数组的长度
        ans = cnt = 0  # ans 计答案，cnt 记录当前连续交替段的长度（链式赋值）
        for i in range(n << 1):  # 扫两圈（2n）以跨越首尾边界，i 取模映射回原数组
            if i and colors[i % n] == colors[(i - 1) % n]:  # 若当前颜色与前一个颜色相同，说明交替在这里断开
                cnt = 1  # 重新开始一段，长度记为 1（即它自己）
            else:  # 否则颜色交替
                cnt += 1  # 交替段长度加一
            ans += i >= n and cnt >= k  # 只在第二圈统计（i >= n），长度达到 k 时布尔值 True 参与加法等价于加 1
        return ans  # 返回交替组总数
