// 题目：3714. 最长的平衡子串 II（Longest Balanced Substring II）
// 思路：平衡子串按出现的不同字符种类数分成三类——只有 1 种、恰好 2 种、3 种全有；前者用游程扫描，中者用差前缀和配哈希表，后者用二维差前缀和配哈希表，三类取最大。
// 时间复杂度：O(n)，三种 calc 各线性扫描；空间复杂度：O(n)，哈希表最多记录 n 个前缀状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestBalanced(string s) {  // s：只含 a、b、c 的字符串；返回最长平衡子串的长度
        int x = calc1(s);  // 只含一种字符的最长平衡子串
        int y = max({calc2(s, 'a', 'b'), calc2(s, 'b', 'c'), calc2(s, 'a', 'c')});  // 恰好含两种字符的最长平衡子串，三种字符两两组合取最大
        int z = calc3(s);  // 三种字符都出现且数量相等的最长平衡子串
        return max({x, y, z});  // 三类情况取最大即为答案
    }  // 方法结束

private:  // 实现细节对外隐藏
    int calc1(const string& s) {  // 统计最长「全为同一字符」的连续段
        int res = 0;  // 结果长度
        int i = 0, n = s.size();  // i：当前连续段起点；n：串长
        while (i < n) {  // 逐段扫描
            int j = i + 1;  // 从 i 之后开始探测相同字符
            while (j < n && s[j] == s[i]) {  // 找到第一个与 s[i] 不同的位置
                ++j;  // 继续向右扩展
            }  // 相同字符段探测结束
            res = max(res, j - i);  // 更新最长连续段长度
            i = j;  // 从新位置开始下一段
        }  // 扫描结束
        return res;  // 返回最长游程长度
    }  // calc1 结束

    int calc2(const string& s, char a, char b) {  // 统计只由 a、b 组成且两者数量相等的最长子串
        int res = 0;  // 结果长度
        int i = 0, n = s.size();  // i：扫描位置；n：串长
        while (i < n) {  // 逐个连续段处理
            while (i < n && s[i] != a && s[i] != b) {  // 跳过不属于 {a, b} 的字符
                ++i;  // 前进
            }  // 定位到本段的起点

            unordered_map<int, int> pos;  // 前缀差值 d -> 首次出现的下标
            pos[0] = i - 1;  // d = 0 的虚拟起点，使从段首开始的子串也能被统计

            int d = 0;  // a 记 +1、b 记 -1 的前缀差值
            while (i < n && (s[i] == a || s[i] == b)) {  // 在当前连续段内扩展
                d += (s[i] == a) ? 1 : -1;  // 更新前缀差值
                auto it = pos.find(d);  // 查找相同差值是否出现过
                if (it != pos.end()) {  // 出现过：两下标之间的 a、b 数量相等
                    res = max(res, i - it->second);  // 更新最长长度
                } else {  // 首次出现该差值
                    pos[d] = i;  // 记录下标
                }  // 差值处理结束
                i++;  // 前进到下一字符
            }  // 本段扩展结束
        }  // 扫描结束
        return res;  // 返回最长长度
    }  // calc2 结束

    static long long f(int x, int y) {  // 把二维差值 (x, y) 压缩成一个 long long 键
        return ((long long) (x + 100000) << 20) | (long long) (y + 100000);  // 加偏移消除负数，再左移 20 位把两维错开
    }  // f 结束

    int calc3(const string& s) {  // 统计三种字符数量都相等的最长子串
        unordered_map<long long, int> pos;  // 二维差值键 -> 首次出现的下标
        pos[f(0, 0)] = -1;  // 空前缀对应下标 -1

        int cnt[3] = {0, 0, 0};  // a、b、c 的前缀出现次数
        int res = 0;  // 结果长度

        for (int i = 0; i < (int) s.size(); i++) {  // 遍历字符串
            char c = s[i];  // 当前字符
            ++cnt[c - 'a'];  // 对应字符计数加一
            int x = cnt[0] - cnt[1];  // 第一维差值：a 与 b 的数量差
            int y = cnt[1] - cnt[2];  // 第二维差值：b 与 c 的数量差
            long long k = f(x, y);  // 压缩成哈希键

            auto it = pos.find(k);  // 查找相同差值是否出现过
            if (it != pos.end()) {  // 出现过：两下标之间三种字符数量相等
                res = max(res, i - it->second);  // 更新最长长度
            } else {  // 首次出现该差值
                pos[k] = i;  // 记录下标
            }  // 差值处理结束
        }  // 遍历结束
        return res;  // 返回最长长度
    }  // calc3 结束
};  // 类定义结束
