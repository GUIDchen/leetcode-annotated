# 题目：1233. 删除子文件夹（Remove Sub-Folders from the Filesystem）
# 思路：按字典序排序后，父文件夹一定先出现；只需与最近保留的路径比较「前缀 + '/'」即可判断子文件夹。
# 时间复杂度：O(n log n + n·L)，排序加逐条前缀比较；空间复杂度：O(n)，保存结果列表。
class Solution:  # LeetCode 约定的题解类
    def removeSubfolders(self, folder: List[str]) -> List[str]:  # folder 是文件夹路径列表，返回去掉子文件夹后的结果
        folder.sort()  # 字典序排序，保证父文件夹排在子文件夹前面
        ans = [folder[0]]  # 第一个路径不可能是别人的子文件夹，先放入答案
        for f in folder[1:]:  # 依次检查剩下的路径
            m, n = len(ans[-1]), len(f)  # m 是最近保留路径长度，n 是当前路径长度
            if m >= n or not (ans[-1] == f[:m] and f[m] == '/'):  # m >= n 时短路不越界；否则要求「前缀 + '/'」才判定为子文件夹
                ans.append(f)  # 不是子文件夹，保留它
        return ans  # 返回过滤后的路径列表
