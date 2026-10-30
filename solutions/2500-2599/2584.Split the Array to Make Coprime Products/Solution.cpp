// 题目：2584. 分割数组使乘积互质（Split the Array to Make Coprime Products）
// 思路：对每个数质因数分解，first 记录质因子首次出现的下标，last[i] 记下标 i 的质因子最远延伸位置；再从左往右扫描并维护最远覆盖 mx，出现 mx < i 即左右两段互质，返回 i。
// 时间复杂度：O(n * sqrt(maxVal)) 的分解代价；空间复杂度：O(n + 质因子种类数)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findValidSplit(vector<int>& nums) {  // nums 为输入数组；返回合法分割点，不存在返回 -1
        unordered_map<int, int> first;  // 质因子 → 它第一次出现的下标
        int n = nums.size();  // 数组长度
        vector<int> last(n);  // last[i]：下标 i 的质因子们最远出现到的下标
        iota(last.begin(), last.end(), 0);  // 初始化为 0,1,2,...,n-1：每个位置至少覆盖自己
        for (int i = 0; i < n; ++i) {  // 从左到右分解每个数
            int x = nums[i];  // 拷贝一份，分解过程中会被不断缩小
            for (int j = 2; j <= x / j; ++j) {  // 只试除到 sqrt(x)，用 x/j 避免 j*j 溢出
                if (x % j == 0) {  // j 是 x 的一个质因子
                    if (first.count(j)) {  // 该质因子之前出现过
                        last[first[j]] = i;  // 更新它首次出现位置能延伸到的右端点
                    } else {  // 该质因子首次出现
                        first[j] = i;  // 记录首次出现的下标
                    }
                    while (x % j == 0) {  // 把因子 j 从 x 中除干净
                        x /= j;  // 去掉一个 j
                    }
                }
            }
            if (x > 1) {  // 剩下的 x>1 说明它本身是最后一个质因子
                if (first.count(x)) {  // 这个质因子之前出现过
                    last[first[x]] = i;  // 同样更新右端点
                } else {  // 首次出现
                    first[x] = i;  // 记录首次出现的下标
                }
            }
        }
        int mx = last[0];  // mx：前缀 [0..i] 中所有质因子能延伸到的最远下标
        for (int i = 0; i < n; ++i) {  // 从左往右找第一个可以切开的位置
            if (mx < i) {  // 前缀的最远延伸仍在本位置左侧，说明已与右侧无公共质因子
                return mx;  // 切在 mx 处即合法分割点
            }
            mx = max(mx, last[i]);  // 否则把当前位置的延伸距离并入 mx
        }
        return -1;  // 整个数组都连在一起，无法分割
    }
};