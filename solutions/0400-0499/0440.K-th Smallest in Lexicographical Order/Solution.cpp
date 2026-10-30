// 题目：440. 字典序的第K小数字（K-th Smallest in Lexicographical Order）
// 思路：把 1..n 看成一棵字典序十叉树，先数出以当前前缀为根的整棵子树节点数 cnt；k >= cnt 就跳过子树换兄弟（curr+1），否则进入子树（curr*10）。
// 复杂度：时间复杂度 O(log^2 n)，最多走 O(log n) 步、每步计数 O(log n)；空间复杂度 O(1)。
class Solution {  // 题解类：求字典序第 k 小的数字
public:  // 公开部分
    int n;  // 把 n 存成成员变量，供下面的 count 辅助函数直接访问

    int findKthNumber(int n, int k) {  // n 是数值上界，k 是 1-based 的序号，返回第 k 小的数字
        this->n = n;  // 参数 n 遮蔽了成员 n，用 this 明确把参数赋给成员
        --k;  // 改成 0-based 计数：数字 1 本身已经算作第 0 个（curr 初值为 1）
        long long curr = 1;  // 从字典序第一个数 1 出发；用 long long 防止 curr*10 溢出 int
        while (k) {  // k 还没归零，说明目标还没走到，继续在十叉树上移动
            int cnt = count(curr);  // 统计以 curr 为前缀的整棵子树一共有多少个节点
            if (k >= cnt) {  // 目标不在当前子树里
                k -= cnt;  // 把整棵子树跳过，k 相应减去它的节点数
                ++curr;  // 换到当前节点的下一个兄弟，即前缀加一
            } else {  // 否则目标就在当前子树里
                --k;  // 先把 curr 自己消费掉，它是这一层最先访问到的数
                curr *= 10;  // 进入子树，走到前缀末尾补零的那个最小数
            }  // 闭合 else
        }  // 闭合 while
        return (int) curr;  // 此时 k 已归零，curr 就是第 k 小的数（转回 int）
    }  // findKthNumber 方法结束

    int count(long long curr) {  // 数出以 curr 为前缀、且不超过 n 的所有数字个数
        long long next = curr + 1;  // next 是同一层右侧兄弟的前缀，用来界定本层的节点区间
        int cnt = 0;  // cnt 累计节点个数
        while (curr <= n) {  // 一层一层往下数，直到当前前缀超过 n
            cnt += min(n - curr + 1, next - curr);  // 本层实际节点数：受上界 n 与右边界 next 双重限制，取较小值
            next *= 10;  // 右边界同样下沉一层，保持与 curr 同层
            curr *= 10;  // 前缀下沉一层，继续统计更深的一层
        }  // 闭合 while
        return cnt;  // 返回整棵前缀子树的节点数
    }  // count 方法结束
};  // Solution 类定义结束