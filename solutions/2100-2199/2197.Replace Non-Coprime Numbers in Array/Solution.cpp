// 题目：2197. 替换数组中的非互质数（Replace Non-Coprime Numbers in Array）
// 思路：用栈模拟：每个数先入栈，再反复取栈顶两个数求 gcd，非互质就把它们替换成最小公倍数，直到栈顶两数互质。
// 时间复杂度：O(n log M)，每个数至多入栈一次、每次合并让栈长度减一，合并次数不超过 n-1；空间复杂度：O(n)，栈最多存 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> replaceNonCoprimes(vector<int>& nums) {  // nums：输入数组；返回值是替换完成后的数组
        vector<int> stk;  // 栈：自底向上保存已处理过的数（可能已被替换成 lcm）
        for (int x : nums) {  // 按原顺序逐个处理数组中的数
            stk.push_back(x);  // 先把当前数压入栈顶，准备参与合并
            while (stk.size() > 1) {  // 只要栈里至少有两个数，就可能还需要继续合并
                x = stk.back();  // 取栈顶的数（它可能是之前合并出来的结果）
                int y = stk[stk.size() - 2];  // 取次栈顶的数
                int g = __gcd(x, y);  // 求最大公约数：g>1 说明两数非互质，必须替换
                if (g == 1) {  // 两数已经互质，合并可以停下
                    break;  // 跳出 while，回到外层处理下一个数组元素
                }  // 结束 if (g == 1)
                stk.pop_back();  // 弹出栈顶，为写入合并结果腾出位置
                stk.back() = 1LL * x * y / g;  // 次栈顶改写为 lcm(x, y) = x * y / g；乘 1LL 先转 long long 防止 int 溢出
            }  // 结束 while：栈顶两数已合并或被判定互质
        }  // 结束 for：所有元素处理完毕
        return stk;  // 栈中自底向上就是最终数组，直接返回
    }  // 结束方法
};  // 结束 Solution 类