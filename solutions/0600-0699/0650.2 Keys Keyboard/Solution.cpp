// 题目：650. 两个键的键盘（2 Keys Keyboard）
// 思路：自顶向下记忆化搜索。n 若可分解成 i × (n/i)，先造出 n/i 个 A，再执行一次 Copy All 与 i-1 次粘贴，总代价 dfs(n/i) + i，对所有因子取最小。
// 时间复杂度：O(n√n)，每个状态枚举到 √n 个候选因子；空间复杂度：O(n)，记忆化数组 f 占 n+1 个位置。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> f;  // 记忆化数组：f[x] 是得到 x 个 A 的最少操作数，-1 表示尚未计算

    int minSteps(int n) {  // n 是目标 A 的个数，返回所需的最少按键次数
        f.assign(n + 1, -1);  // 把记忆化数组初始化为 n+1 个 -1，表示所有状态都未计算
        return dfs(n);  // 从目标 n 开始自顶向下递推答案
    }

    int dfs(int n) {  // 返回打印出 n 个 A 所需的最少按键次数
        if (n == 1) return 0;  // 只有一个 A 时无需任何操作，这是递归边界
        if (f[n] != -1) return f[n];  // 已经算过就直接取缓存，避免重复搜索
        int ans = n;  // 最坏情况基线：一次 Copy All 再粘贴 n-1 次，共 n 次按键
        for (int i = 2; i * i <= n; ++i) {  // 只枚举到 √n，因为因子成对出现，另一半由递归覆盖
            if (n % i == 0) {  // i 是 n 的因子，可把 n 拆成 i 组、每组 n/i 个
                ans = min(ans, dfs(n / i) + i);  // 先造 n/i 个，再 Copy All 并粘贴 i-1 次，总代价 dfs(n/i) + i
            }
        }
        f[n] = ans;  // 把该状态的最优解记入缓存
        return ans;  // 返回最少按键次数
    }
};