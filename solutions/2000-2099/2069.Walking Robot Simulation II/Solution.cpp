// 题目：2069. 模拟行走机器人 II（Walking Robot Simulation II）
// 思路：机器人沿矩形边框逆时针循环行走，一圈步数为周长 p；把累计步数对 p 取模，再按四段边界公式换算成坐标与朝向。
// 时间复杂度：构造 O(1)，step O(1)，getPos/getDir O(1)；空间复杂度：O(1)，只保存常数个状态变量。
class Robot {  // 按题意实现的 Robot 类
public:  // 接口对外可见
    int mx, my, p, cur;  // mx/my 是最右/最上坐标，p 是一圈步数，cur 是对 p 取模后的累计步数
    bool moved;  // moved 标记是否调用过 step，用来区分初始朝向

    Robot(int width, int height) {  // 构造函数：width、height 为网格宽高
        mx = width - 1;  // 最右列的 x 坐标
        my = height - 1;  // 最上行的 y 坐标
        p = 2 * mx + 2 * my;  // 一圈的步数（周长）为 2*mx + 2*my
        cur = 0;  // 初始位置在 (0,0)，累计步数为 0
        moved = false;  // 初始还没有移动过
    }

    void step(int num) {  // 前进 num 步
        moved = true;  // 记录已经移动过，朝向按当前位置判断
        cur = (cur + num) % p;  // 步数对周长取模，避免重复绕圈
    }

    vector<int> getPos() {  // 返回当前坐标 [x, y]
        int d = cur;  // d 是取模后的累计步数，用它定位坐标
        int mx = this->mx, my = this->my;  // 把成员变量取到局部变量，便于书写

        if (0 <= d && d <= mx) {  // 第一段：沿底边向东，x 在 0..mx，y 恒为 0
            return {d, 0};  // 坐标为 (d, 0)
        }
        if (mx < d && d <= mx + my) {  // 第二段：沿右边向北走
            return {mx, d - mx};  // x 恒为 mx，y 为 d - mx
        }
        if (mx + my < d && d <= 2 * mx + my) {  // 第三段：沿顶边向西走
            return {mx - (d - (mx + my)), my};  // x 从 mx 往回减，y 恒为 my
        }
        return {0, my - (d - (2 * mx + my))};  // 第四段：沿左边向南，回到起点前
    }

    string getDir() {  // 返回当前朝向
        int d = cur;  // d 是取模后的累计步数
        int mx = this->mx, my = this->my;  // 把成员变量取到局部变量

        if (!moved) {  // 从未移动过时，题面规定朝向为 East
            return "East";  // 未移动过，直接返回 East
        }
        if (1 <= d && d <= mx) {  // 第一段向东（d 为 0 表示刚走满一圈，归到第四段处理，故从 1 开始）
            return "East";  // 向东
        } else if (mx < d && d <= mx + my) {  // 第二段向北
            return "North";  // 向北
        } else if (mx + my < d && d <= 2 * mx + my) {  // 第三段向西
            return "West";  // 向西
        }
        return "South";  // 剩余情况：第四段向南
    }
};

// 以下是 LeetCode 自动生成的调用示例注释块，原样保留，不参与编译
/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
