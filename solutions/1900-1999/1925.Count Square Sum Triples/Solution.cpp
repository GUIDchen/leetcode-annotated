// 题目：1925. 统计平方和三元组的数目（Count Square Sum Triples）
// 思路：双重循环枚举两条直角边 a、b，算出 a²+b² 后开方取整得到候选斜边 c，再验证 c 在范围内且 c² 恰好等于该和。
// 时间复杂度：O(n²)，两层循环各 n 次；空间复杂度：O(1)，只使用若干整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countTriples(int n) {  // n：上界，a、b、c 都必须落在 [1, n] 内
        int ans = 0;  // 计数器：满足条件的三元组个数
        for (int a = 1; a < n; ++a) {  // 枚举第一条直角边 a
            for (int b = 1; b < n; ++b) {  // 枚举第二条直角边 b
                int x = a * a + b * b;  // 两条直角边的平方和
                int c = static_cast<int>(sqrt(x));  // 开方并向下取整，得到可能的斜边
                if (c <= n && c * c == x) {  // 斜边不越界且平方能还原成 x，说明 x 是完全平方数
                    ++ans;  // 找到一个合法三元组，计数加一
                }
            }
        }
        return ans;  // 返回三元组总数
    }
};
