# 题目：1088. 易混淆数 II（Confusing Number II）
# 思路：按位 DFS 枚举只含 {0,1,6,8,9} 的数，用 limit 标记前缀是否紧贴上界 n；某一位取满时后缀才受限。枚举到最低位后用 check 判断该数旋转 180° 后是否与原数不同并计数。
# 时间复杂度：O(5^L · L)，L 为 n 的十进制位数（每个合法数再做一次 O(L) 的 check）；空间复杂度：O(L)，只有递归栈。
class Solution:  # LeetCode 约定的题解类
    def confusingNumberII(self, n: int) -> int:  # 统计 [1, n] 中易混淆数的个数
        def check(x: int) -> bool:  # 内层函数：判断 x 旋转 180° 后是否与原数不同
            y, t = 0, x  # y 存旋转结果，t 是逐位取数的临时变量
            while t:  # t 变成 0 说明所有位都处理完了
                t, v = divmod(t, 10)  # 取出最低位 v，同时把 t 右移一位
                y = y * 10 + d[v]  # 把映射后的数字接到 y 末尾，等价于「倒序 + 逐位映射」
            return x != y  # 旋转后与原数不同才是易混淆数

        def dfs(pos: int, limit: bool, x: int) -> int:  # 内层 DFS：pos 当前位，limit 表示前缀是否仍贴着上界，x 是已构造的前缀数值
            if pos >= len(s):  # 已经填满了所有数位
                return int(check(x))  # 是易混淆数就计 1，否则计 0
            up = int(s[pos]) if limit else 9  # 当前位的枚举上界：贴上界时不能超过 s[pos]，否则可到 9
            ans = 0  # 累计当前分支下的易混淆数个数
            for i in range(up + 1):  # 枚举当前位可填的数字
                if d[i] != -1:  # 该数字旋转后仍然不是非法数字（2、3、4、5、7 非法）
                    ans += dfs(pos + 1, limit and i == up, x * 10 + i)  # 递归下一位；只有本位上界且取到上界时才继续贴住 limit
            return ans  # 返回本层统计到的个数

        d = [0, 1, -1, -1, -1, -1, 9, -1, 8, 6]  # 数字到「旋转 180° 后的数字」的映射，-1 表示旋转后不是合法数字
        s = str(n)  # 上界转成字符串，便于按位取上界 digit
        return dfs(0, True, 0)  # 从最高位、紧贴上界、前缀为 0 开始统计
