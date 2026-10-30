// 题目：1088. 易混淆数 II（Confusing Number II）
// 思路：数位 DFS：从高位到低位只枚举能旋转的数字 {0,1,6,8,9}，用 limit 标记前缀是否紧贴上界 n；枚举完所有位后用 check 判断该数旋转 180° 后是否与原数不同并计数。
// 时间复杂度：O(5^L · L)，L 为 n 的十进制位数（每个合法数再做一次 O(L) 的 check）；空间复杂度：O(L)，只有递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int confusingNumberII(int n) {  // 统计 [1, n] 中易混淆数的个数
        string s = to_string(n);  // 上界转成字符串，方便按下标取每一位的上界数字
        int d[10] = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};  // 数字到「旋转 180° 后的数字」的映射，-1 表示旋转后不是合法数字（2、3、4、5、7）
        auto check = [&](int x) -> bool {  // lambda：判断 x 旋转 180° 后是否与原数不同
            int y = 0;  // y 保存旋转后的结果
            for (int t = x; t; t /= 10) {  // 从低位到高位遍历 x 的每一位
                int v = t % 10;  // 取出当前最低位数字
                y = y * 10 + d[v];  // 把映射后的数字接到 y 末尾，等价于「倒序 + 逐位映射」
            }  // 结束逐位处理
            return x != y;  // 旋转后与原数不同才是易混淆数
        };  // 结束 check lambda 的定义
        function<int(int, int, int)> dfs = [&](int pos, int limit, int x) -> int {  // 数位 DFS：pos 当前位，limit 表示是否仍贴着上界，x 是已构造的前缀数值
            if (pos >= s.size()) {  // 所有数位都已经填满
                return check(x);  // 判断该数是否为易混淆数，true 会被隐式转成 1
            }  // 结束递归出口分支
            int up = limit ? s[pos] - '0' : 9;  // 当前位的枚举上界：贴上界时不能超过 s[pos]，否则可以到 9
            int ans = 0;  // 累计当前位置下的合法个数
            for (int i = 0; i <= up; ++i) {  // 枚举当前位可以填的数字
                if (d[i] != -1) {  // 只有能旋转的数字才允许出现在易混淆数里
                    ans += dfs(pos + 1, limit && i == up, x * 10 + i);  // 递归下一位；只有本位取到上界且仍然贴住时才继续受到限制
                }  // 结束当前数字的枚举
            }  // 结束逐位枚举循环
            return ans;  // 返回本层的统计结果
        };  // 结束 dfs 的定义
        return dfs(0, 1, 0);  // 从最高位、紧贴上界、前缀为 0 开始统计
    }  // 结束方法体
};  // 类定义结束