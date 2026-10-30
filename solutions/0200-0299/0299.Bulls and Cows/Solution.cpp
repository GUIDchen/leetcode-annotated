// 题目：299. 猜数字游戏（Bulls and Cows）
// 思路：同位置数字相同就是公牛（A）；其余位置分别统计 0~9 各数字出现次数，对每种数字取两串次数的较小值累加即奶牛（B）。
// 时间复杂度：O(n + 10)，n 为数字串长度；空间复杂度：O(1)，只用两个长度为 10 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string getHint(string secret, string guess) {  // secret：答案数字串；guess：猜测数字串
        int x = 0, y = 0;  // x 记公牛数，y 记奶牛数
        int cnt1[10]{};  // secret 中尚未配对数字的出现次数，下标 0~9
        int cnt2[10]{};  // guess 中尚未配对数字的出现次数，下标 0~9
        for (int i = 0; i < secret.size(); ++i) {  // 逐位同时比较两个串
            int a = secret[i] - '0', b = guess[i] - '0';  // 把字符数字转成 0~9 的下标
            if (a == b) {  // 同位置数字相同，是一只公牛
                ++x;  // 公牛数加一
            } else {  // 否则各自计数，留待后面配对成奶牛
                ++cnt1[a];  // 记录 secret 中该数字的出现次数
                ++cnt2[b];  // 记录 guess 中该数字的出现次数
            }  // if/else 结束
        }  // for 循环结束
        for (int i = 0; i < 10; ++i) {  // 枚举 0~9 每一种数字
            y += min(cnt1[i], cnt2[i]);  // 两串中该数字出现次数的较小值就是能配对成奶牛的个数
        }  // for 循环结束
        return to_string(x) + "A" + to_string(y) + "B";  // 按「xAyB」的格式拼出结果
    }  // 方法结束
};  // 类定义结束