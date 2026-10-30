// 题目：489. 扫地机器人（Robot Room Cleaner）
// 思路：把房间抽象成格子坐标系，从 (0,0) 朝向 0 开始 DFS；每到一个格子先 clean，再尝试四个方向，能 move 就递归，递归返回后用「右转两次 + move + 右转两次」把机器人还原到原位置和原朝向。
// 时间复杂度：O(m·n)，每个可达格子至多访问一次（每次按 4 个方向扩展）；空间复杂度：O(m·n)，vis 集合与递归栈的深度。
/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void cleanRoom(Robot& robot) {  // robot：题目提供的机器人接口，只能通过 move/turnLeft/turnRight/clean 感知房间
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：上、右、下、左四组 (dx, dy)，末尾多补一个 -1，方便用 dirs[nd + 1] 直接取列增量
        set<pair<int, int>> vis;  // 记录已经清理过的坐标，房间可能有环，必须靠它避免重复搜索与无限递归
        function<void(int, int, int)> dfs = [&](int i, int j, int d) {  // 递归函数：i、j 是相对起点的坐标，d 是机器人当前朝向（0~3 对应上右下左）
            robot.clean();  // 第一步先清理当前格子
            vis.insert({i, j});  // 标记当前格子已访问
            for (int k = 0; k < 4; ++k) {  // 四个方向都要尝试
                int nd = (d + k) % 4;  // 始终在当前朝向上顺时针转 k 次，得到本次要探索的方向
                int x = i + dirs[nd], y = j + dirs[nd + 1];  // 目标格子的坐标（行增量为 dirs[nd]，列增量为 dirs[nd + 1]）
                if (!vis.count({x, y}) && robot.move()) {  // 目标格子没走过、且前方确实是空地（move 成功，机器人已进入目标格）
                    dfs(x, y, nd);  // 进入目标格子继续深搜
                    robot.turnRight();  // 回溯第一步：原地右转 180 度中的第一次
                    robot.turnRight();  // 回溯第二步：第二次右转，此时朝向正好反转，面朝来路
                    robot.move();  // 沿来路退回上一格，恢复递归前的位置
                    robot.turnRight();  // 再把朝向转回来：右转两次中的第一次
                    robot.turnRight();  // 第二次右转，朝向还原成进入目标格时的 nd
                }  // 试探分支结束
                robot.turnRight();  // 顺时针转 90 度，让下一轮循环的 (d + k) % 4 指向下一个方向
            }  // 四个方向都尝试完毕
        };  // lambda（dfs）定义结束
        dfs(0, 0, 0);  // 从相对原点 (0, 0) 出发，初始朝向设为 0
    }  // 方法结束，整间连通的房间都已被清理
};  // 类定义结束