// 题目：2071. 你可以安排的最多任务数目（Maximum Number of Tasks You Can Assign）
// 思路：排序后二分答案 x，判定时只让最强的 x 名工人去做最小的 x 个任务，用双端队列维护候选任务：能不吃药就做最小的，必须吃药就做最大的。
// 时间复杂度：O((n + m) log(n + m) + min(n, m) · n)，二分 log 次、每次线性判定；空间复杂度：O(n)，队列最多存 n 个任务。
class Solution {  // 题解类：所有题解方法都写在这里
public:  // 方法对外可见（LeetCode 约定）
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {  // tasks 是任务耗时，workers 是工人能力，pills 是药丸数，strength 是药丸加成
        sort(tasks.begin(), tasks.end());  // 任务耗时升序，方便总是优先处理最省力的任务
        sort(workers.begin(), workers.end());  // 工人能力升序，方便取最强的 x 名工人
        int n = tasks.size(), m = workers.size();  // n 为任务数，m 为工人数
        int left = 0, right = min(m, n);  // 二分区间：最多能完成 min(m, n) 个任务
        auto check = [&](int x) {  // 判定函数：能否完成恰好 x 个任务（x 个最小的任务对 x 名最强的工人）
            int p = pills;  // 本次判定可用的药丸数，每个药丸让一名工人能力 +strength
            deque<int> q;  // 单调队列：存放当前工人「加药丸后够得着」的任务耗时，内部保持升序
            int i = 0;  // 指向最小的、尚未进入候选队列的任务下标
            for (int j = m - x; j < m; ++j) {  // 让最强的 x 名工人上场，从强到弱依次分派
                while (i < x && tasks[i] <= workers[j] + strength) {  // 把该工人吃药丸后仍能完成的候选任务全部入队
                    q.push_back(tasks[i++]);  // 任务入队，候选指针前移
                }  // while 结束：候选任务收集完毕
                if (q.empty()) {  // 队列为空说明连最省力的任务都做不了，x 个任务不可能完成
                    return false;  // 判定失败
                }  // if 结束
                if (q.front() <= workers[j]) {  // 队头是最省力的候选任务，不用药丸就能完成：直接分给当前工人
                    q.pop_front();  // 从队头取走这个任务，省下药丸留给后面的强工人
                } else if (p == 0) {  // 不吃药做不了，而药丸已经用完
                    return false;  // 判定失败
                } else {  // 还有药丸：吃药丸强行完成一个任务
                    --p;  // 消耗一颗药丸
                    q.pop_back();  // 取走队列里最大的任务，把省力的任务留给后面更弱的工人
                }  // else 块结束
            }  // for 循环结束：x 名工人全部分派完毕
            return true;  // x 个任务全部分派成功
        };  // check 判定函数定义结束
        while (left < right) {  // 二分答案，寻找满足 check 的最大 x
            int mid = (left + right + 1) >> 1;  // 上取整的中点，配合下面 left = mid 避免死循环
            if (check(mid)) {  // mid 个任务可以完成
                left = mid;  // 答案至少是 mid，收缩左边界
            } else {  // 否则 mid 不可行
                right = mid - 1;  // 答案更小，收缩右边界
            }  // else 块结束
        }  // while 结束：二分收敛
        return left;  // left 即最多能完成的任务数目
    }  // 类定义结束
};