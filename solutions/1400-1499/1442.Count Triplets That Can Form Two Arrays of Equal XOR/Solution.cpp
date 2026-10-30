// 题目：1442. 形成两个异或相等数组的三元组数目（Count Triplets That Can Form Two Arrays of Equal XOR）
// 思路：a == b 等价于 arr[i..k] 的异或和为 0；固定左端 i 向右累加异或，一旦为 0 就有 k-i 个合法的 j。
// 时间复杂度：O(n^2)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countTriplets(vector<int>& arr) {  // arr 是输入数组
        int ans = 0, n = arr.size();  // ans 统计合法三元组个数，n 是数组长度
        for (int i = 0; i < n; ++i) {  // 枚举三元组的左端点 i
            int s = arr[i];  // 以 i 开头的区间异或和，先把 arr[i] 放进去
            for (int k = i + 1; k < n; ++k) {  // 枚举右端点 k，至少比 i 大 1 才能分成两个非空数组
                s ^= arr[k];  // 把 arr[k] 并入异或和
                if (s == 0) {  // 区间异或为 0，说明前一段与后一段异或相等
                    ans += k - i;  // 中间的分界点 j 可取 i+1 到 k 共 k-i 个位置
                }
            }
        }  // 返回合法三元组总数
        return ans;
    }
};
