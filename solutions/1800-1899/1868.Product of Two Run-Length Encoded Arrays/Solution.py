# 题目：1868. 两个行程编码数组的积（Product of Two Run-Length Encoded Arrays）
# 思路：双指针按行程对齐切分两个编码数组，每次取两段剩余长度的较小值作为公共长度，乘积相同则与答案末段合并。
# 时间复杂度：O(m + n)，两数组的行程段各自只被消耗一次；空间复杂度：O(m + n)，答案最多有 m + n 段。
class Solution:  # LeetCode 约定的题解类
    def findRLEArray(  # encoded1、encoded2：行程编码数组，每项为 [值, 连续段长度]
        self, encoded1: List[List[int]], encoded2: List[List[int]]
    ) -> List[List[int]]:  # 返回值同样是 [值, 长度] 形式的行程编码
        ans = []  # 答案：用 [值, 段长度] 累积乘积的行程编码
        j = 0  # j：encoded2 中当前正在消耗的行程段下标
        for vi, fi in encoded1:  # 依次取出 encoded1 每段的值 vi 与本段长度 fi
            while fi:  # fi 还有剩余长度，就继续和 encoded2 对齐切分
                f = min(fi, encoded2[j][1])  # 公共长度取两段剩余长度的较小值
                v = vi * encoded2[j][0]  # 两段的值相乘，得到这段公共区间的乘积
                if ans and ans[-1][0] == v:  # 与答案末段乘积相同则合并，保证行程编码尽量短
                    ans[-1][1] += f  # 末段长度累加本次段长
                else:  # 乘积不同，必须新开一段
                    ans.append([v, f])  # 追加新的 [乘积, 长度]
                fi -= f  # 扣掉 encoded1 本次已经消耗的长度
                encoded2[j][1] -= f  # encoded2 当前段同步扣减相同长度
                if encoded2[j][1] == 0:  # 当前段已消耗完
                    j += 1  # 指针右移，换下一段
        return ans  # 返回乘积的行程编码结果
