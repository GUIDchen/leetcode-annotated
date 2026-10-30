// 题目：1787. 使所有区间的异或结果为零（Make the XOR of All Segments Equal to Zero）
// 思路：所有长度为 k 的区间异或为 0 等价于 a[i] == a[i % k] 且同一列异或为 0；按列做状态压缩 DP，f[x] 表示当前前缀异或为 x 的最小修改数。
// 时间复杂度：O(k * 2^10 * 列内不同值个数)，最坏 O(k * 2^20)；空间复杂度：O(2^10 + n)，cnt 统计与两个 DP 数组。
class Solution {
public:
    int minChanges(vector<int>& nums, int k) {  // 主函数：返回最少修改多少个元素，能使所有长度为 k 的区间异或和都为 0
        int n = 1 << 10;  // DP 的状态空间：元素都小于 2^10，所以异或值只需枚举 0..1023
        unordered_map<int, int> cnt[k];  // cnt[r][x]：下标模 k 余 r 的那一列里，数值 x 一共出现了多少次
        vector<int> size(k);  // size[r]：第 r 列一共有多少个位置
        for (int i = 0; i < nums.size(); ++i) {  // 遍历整个数组，把每个元素归到它所属的列
            cnt[i % k][nums[i]]++;  // 第 i 个元素属于第 i%k 列，累计该列中这个数值的出现次数
            size[i % k]++;  // 该列的长度加一
        }
        vector<int> f(n, 1 << 30);  // f[x]：处理完前若干列、当前异或值为 x 时的最少修改次数，先全部置为极大值
        f[0] = 0;  // 边界：一列都没处理时异或为 0，代价为 0
        for (int i = 0; i < k; ++i) {  // 逐列推进 DP，每轮 f 表示处理完前 i 列的结果
            int mi = *min_element(f.begin(), f.end());  // 取出上一轮的最小代价，作为「整列全部替换」这一转移的基准
            vector<int> g(n, mi + size[i]);  // 方案一：整列 size[i] 个元素全部换成同一目标值，代价固定为列长，可从任意旧状态转移
            for (int j = 0; j < n; ++j) {  // 枚举这一列处理完之后，前 i+1 列的异或值 j
                for (auto& [v, c] : cnt[i]) {  // 枚举这一列中「保留不动」的数值 v 及其出现次数 c
                    g[j] = min(g[j], f[j ^ v] + size[i] - c);  // 方案二：保留 c 个 v，其余 size[i]-c 个改成 v，故旧异或必须是 j^v
                }
            }
            f = move(g);  // 用移动赋值把新状态交给 f，避免整表拷贝，进入下一列
        }
        return f[0];  // 全部列处理完后异或为 0 的最小代价就是答案
    }
};  // 题解类定义结束