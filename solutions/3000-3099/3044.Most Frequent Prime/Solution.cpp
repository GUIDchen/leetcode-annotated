// 题目：3044. 出现频率最高的质数（Most Frequent Prime）
// 核心思路：以每个格子为起点沿 8 个方向不断拼接数字，统计所有拼出的质数的出现次数，取次数最多（并列取数值最大）的质数。
// 时间复杂度：O(m * n * max(m, n) * sqrt(V))，枚举起点与路径后还要判定质数；空间复杂度：O(m * n * max(m, n))，用于统计不同质数的次数。
class Solution {
public:
    int mostFrequentPrime(vector<vector<int>>& mat) {  // mat：数字矩阵，返回沿 8 个方向拼接出的质数中出现次数最多的那个
        int m = mat.size(), n = mat[0].size();  // m、n：矩阵的行数与列数，用于边界判断
        unordered_map<int, int> cnt;  // cnt：键是拼出的质数，值是它在所有路径中出现的次数
        for (int i = 0; i < m; ++i) {  // 枚举起点格子的行下标 i
            for (int j = 0; j < n; ++j) {  // 枚举起点格子的列下标 j
                for (int a = -1; a <= 1; ++a) {  // 方向行增量 a 取 -1、0、1，表示向上、不动、向下
                    for (int b = -1; b <= 1; ++b) {  // 方向列增量 b 取 -1、0、1，表示向左、不动、向右
                        if (a == 0 && b == 0) {  // a、b 同时为 0 时方向无效
                            continue;  // 跳过这个无效方向，避免原地打转
                        }
                        int x = i + a, y = j + b, v = mat[i][j];  // x、y 是下一步的坐标，v 是从起点开始已拼出的数字
                        while (x >= 0 && x < m && y >= 0 && y < n) {  // 只要坐标还在矩阵内，就沿该方向一直延伸
                            v = v * 10 + mat[x][y];  // 把新格子的数字接到 v 末尾，得到更长的数
                            if (isPrime(v)) {  // 判断当前拼出的数是否为质数，是则计入频次
                                cnt[v]++;  // 该质数的出现次数加一
                            }
                            x += a;  // 行坐标沿方向推进
                            y += b;  // 列坐标沿方向推进
                        }
                    }
                }
            }
        }
        int ans = -1, mx = 0;  // ans：出现次数最多的质数（-1 表示还没有答案）；mx：当前最高出现次数
        for (auto& [v, x] : cnt) {  // 遍历统计表，每个键值对分别是质数 v 与出现次数 x
            if (mx < x || (mx == x && ans < v)) {  // 次数更多时更新；次数相同时取数值更大的质数
                mx = x;  // 记录新的最高次数
                ans = v;  // 记录对应的质数
            }
        }
        return ans;  // 返回出现频率最高的质数，没有质数时返回 -1
    }  // 方法结束

private:  // 私有辅助方法：判断一个整数是否为质数
    bool isPrime(int n) {  // n：待判定的整数
        for (int i = 2; i <= n / i; ++i) {  // 只需试除到 sqrt(n)；写成 i <= n / i 既避免溢出，也不用调用开方函数
            if (n % i == 0) {  // 找到因子说明不是质数
                return false;  // 存在因子则立即返回 false
            }
        }
        return true;  // 没有找到任何因子，n 是质数
    }  // 辅助方法结束
};  // 题解类结束