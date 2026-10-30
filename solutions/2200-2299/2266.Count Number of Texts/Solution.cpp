// 题目：2266. 统计打字方案数（Count Number of Texts）
// 思路：把按键序列按「连续相同字符」分段；长度为 k 的一段，按键为 7 或 9（这两个键有 4 个字母）时方案数为 g[k]，否则为 f[k]；f、g 是预处理好的台阶型递推（f 取前三项和，g 取前四项和），各段方案数相乘并取模。
// 时间复杂度：预处理 O(N)（N = 1e5+10，全局只做一次），每次调用 O(|pressedKeys|)；空间复杂度：O(N)，用于保存两个递推表。
const int mod = 1e9 + 7;  // 取模常量，避免方案数过大溢出
const int n = 1e5 + 10;  // 预处理上界，略大于题目给出的最大按键长度 1e5
long long f[n], g[n];  // f[k]：普通键（3 个字母）长度 k 的连续段方案数；g[k]：7/9 键（4 个字母）长度 k 的连续段方案数

int init = []() {  // 全局静态初始化：借 lambda 在 main 之前把递推表预先算好
    f[0] = g[0] = 1;  // 长度 0 时只有「空序列」这 1 种方案
    f[1] = g[1] = 1;  // 长度 1：只能按一次，1 种方案
    f[2] = g[2] = 2;  // 长度 2：整体按或拆成两段各按一次，共 2 种
    f[3] = g[3] = 4;  // 长度 3：最后一段可以是 1、2、3 个字母，共 4 种
    for (int i = 4; i < n; ++i) {  // 从长度 4 开始按递推式填表
        f[i] = (f[i - 1] + f[i - 2] + f[i - 3]) % mod;  // 3 字母键：最后一段可能是 1/2/3 个相同字母
        g[i] = (g[i - 1] + g[i - 2] + g[i - 3] + g[i - 4]) % mod;  // 4 字母键：最后一段可能是 1/2/3/4 个相同字母
    }
    return 0;  // lambda 返回 0，作为 init 变量的初值
}();

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countTexts(string pressedKeys) {  // pressedKeys：按键序列
        long long ans = 1;  // 乘法累加器，初始为 1（乘法的单位元）
        for (int i = 0, n = pressedKeys.length(); i < n; ++i) {  // i 是当前连续段的起点；这里局部 n 遮蔽了同名全局常量
            char c = pressedKeys[i];  // 当前连续段的按键字符
            int j = i;  // j 用于向右扩展当前段
            while (j + 1 < n && pressedKeys[j + 1] == c) {  // 只要下一个字符与 c 相同就继续扩展
                ++j;  // 右端点右移一位
            }
            int cnt = j - i + 1;  // 当前连续相同字符的数量
            ans = c == '7' || c == '9' ? ans * g[cnt] : ans * f[cnt];  // 7/9 键有 4 个字母用 g，其余键用 f
            ans %= mod;  // 每乘一次就取模，防止 long long 溢出
            i = j;  // 直接跳到本段末尾，外层循环的 ++i 正好指向下一段起点
        }
        return ans;  // 各段方案数相乘即为整串的方案总数
    }
};
