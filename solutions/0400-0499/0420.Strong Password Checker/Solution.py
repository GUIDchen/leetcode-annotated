# 题目：420. 强密码检验器（Strong Password Checker）
# 思路：按长度分三段——太短（<6）插入/替换取较大值；长度合法只需替换重复段并补字符种类；太长（>20）先用重复段长度模 3 的余数高效删除，再用删 2 或删 3 抵扣替换。
# 时间复杂度：O(n)，只常数遍扫描；空间复杂度：O(1)，只用几个计数变量。
class Solution:  # LeetCode 约定的题解类
    def strongPasswordChecker(self, password: str) -> int:  # password 是待检测的密码，返回使密码变强所需的最少操作次数
        def countTypes(s):  # 内部函数：统计密码里出现了几类字符（小写/大写/数字）
            a = b = c = 0  # a、b、c 分别标记三类字符是否出现过
            for ch in s:  # 逐字符判断
                if ch.islower():  # 小写字母
                    a = 1  # 标记小写
                elif ch.isupper():  # 大写字母
                    b = 1  # 标记大写
                elif ch.isdigit():  # 数字
                    c = 1  # 标记数字
            return a + b + c  # 返回字符种类数（0 到 3）

        types = countTypes(password)  # 先统计字符种类与密码长度
        n = len(password)  # n 是密码长度
        if n < 6:  # 太短（< 6）：插入和替换都能顺带补字符种类，取较大值
            return max(6 - n, 3 - types)  # 返回最少操作数
        if n <= 20:  # 长度合法（6 到 20）：只需替换重复字符并补足字符种类
            replace = cnt = 0  # replace 是替换次数，cnt 是当前连续相同字符数
            prev = '~'  # prev 是哨兵，保证第一轮进入 else 分支
            for curr in password:  # 逐字符扫描
                if curr == prev:  # 与前一字符相同，连续长度加一
                    cnt += 1  # 连续计数加一
                else:  # 一段连续相同字符结束
                    replace += cnt // 3  # 长度 k 的连续段需要 k // 3 次替换
                    cnt = 1  # 新一段从 1 开始计数
                    prev = curr  # 更新 prev 为当前字符
            replace += cnt // 3  # 收尾：最后一段也要累加替换需求
            return max(replace, 3 - types)  # 替换与补种类可合并进行，取较大值
        replace = cnt = 0  # 太长（> 20）：remove 是必删字符数，remove2 记录长度余 1 的重复段数
        remove, remove2 = n - 20, 0  # 初始化删除额度与第二类重复段计数
        prev = '~'  # prev 哨兵
        for curr in password:  # 逐字符扫描，切分出每一段连续相同字符
            if curr == prev:  # 连续长度加一
                cnt += 1  # 连续计数加一
            else:  # 一段连续相同字符结束
                if remove > 0 and cnt >= 3:  # 还有删除额度且这段长度不小于 3
                    if cnt % 3 == 0:  # 长度是 3 的倍数：删 1 个字符即可减少一次替换需求
                        remove -= 1  # 消耗一个删除额度
                        replace -= 1  # 替换需求减一
                    elif cnt % 3 == 1:  # 长度余 1：记录下来，后面删 2 个字符也能省一次替换
                        remove2 += 1  # 这类重复段计数加一
                replace += cnt // 3  # 仍按长度除以 3 累加替换需求
                cnt = 1  # 重置当前段计数
                prev = curr  # 更新 prev
        if remove > 0 and cnt >= 3:  # 收尾处理最后一段（逻辑与循环内相同）
            if cnt % 3 == 0:  # 最后一段长度是 3 的倍数
                remove -= 1  # 消耗一个删除额度
                replace -= 1  # 替换需求减一
            elif cnt % 3 == 1:  # 最后一段长度余 1
                remove2 += 1  # 计入 remove2
        replace += cnt // 3  # 累加最后一段的替换需求
        use2 = min(replace, remove2, remove // 2)  # 优先用删 2 个字符的方式消掉替换需求，取三者最小
        replace -= use2  # 替换需求相应减少
        remove -= use2 * 2  # 消耗 2 倍的删除额度

        use3 = min(replace, remove // 3)  # 剩下的替换需求用删 3 个字符来解决
        replace -= use3  # 替换需求减少
        remove -= use3 * 3  # 消耗 3 倍的删除额度
        return n - 20 + max(replace, 3 - types)  # 总操作数 = 必删次数 + 剩余替换与补种类所需的较大值
