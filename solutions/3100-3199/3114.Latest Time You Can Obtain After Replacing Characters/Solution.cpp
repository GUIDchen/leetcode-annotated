// 题目：3114. 替换字符可以得到的最晚时间（Latest Time You Can Obtain After Replacing Characters）
// 思路：从最晚的 11:59 开始倒序枚举所有合法时刻，第一个与模式 s 兼容（非 '?' 的位置全部相同）的时刻就是答案。
// 时间复杂度：O(12 × 60 × 5) = O(1)，枚举次数固定；空间复杂度：O(1)，只用了一个 6 字节的字符数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string findLatestTime(string s) {  // s 是形如 "hh:mm" 的时间模式，'?' 表示该位可以替换
        for (int h = 11;; h--) {  // 小时从最晚的 11 开始倒序尝试；题目保证有解，故省略终止条件
            for (int m = 59; m >= 0; m--) {  // 分钟从最晚的 59 开始倒序尝试
                char t[6];  // 缓冲区，存放格式化后的 "hh:mm"，加上结尾 '\0' 共 6 个字节
                sprintf(t, "%02d:%02d", h, m);  // 格式化成两位小时、两位分钟的字符串
                bool ok = true;  // 标记当前时刻是否与模式 s 兼容
                for (int i = 0; i < s.length(); i++) {  // 逐位比对当前时刻与模式
                    if (s[i] != '?' && s[i] != t[i]) {  // 模式中确定的位与实际时刻不一致
                        ok = false;  // 说明该时刻不合法
                        break;  // 无需再比对后面的位置
                    }
                }
                if (ok) {  // 找到第一个（也就是最晚的）兼容时刻
                    return t;  // 直接返回，字符数组会隐式转换成 string
                }
            }
        }
    }
};