#include <tubex.h>

using namespace std;
using namespace tubex;

int main()
{
Vector x_truth({2.,1.,M_PI/6});
Vector y_truth({6.,M_PI/6});
Vector m_truth({5.,6.2});
IntervalVector x{{-oo,+oo},{-oo,+oo}};
IntervalVector y{{6},{M_PI/6}};
y[0].inflate(0.3);
y[1].inflate(0.1);
IntervalVector m{{5.},{6.2}};
m.inflate(0.2);
Interval interval_rho = y[0];
Interval interval_theta = x_truth[2] + y[1];
//reseau de contracteur
ContractorNetwork cn;
CtcFunction ctc_sub(Function("x","y","a","x-y-a"));
CtcFunction ctc_sqr(Function("x","c","sqr(x)-c"));
CtcFunction ctc_add(Function("x","y","d","x+y-d"));
CtcFunction ctc_sqrt(Function("x","e","sqrt(x)-e"));
Interval a,b,c,d,e,d1,d2 = Interval{-oo,oo};

cout<<x<<endl;
cout<<m<<endl;
cout<<y<<endl;
cn.add(ctc_sub,{x[0],m[0],a});
cn.add(ctc_sub,{x[1],m[1],b});
cn.add(ctc_sqr,{a,c});
cn.add(ctc_sqr,{b,d});
cn.add(ctc_add,{c,b,e});
cn.add(ctc_sqrt,{e,y[0]});
cn.add(ctc::polar,{d1,d2,y[0],interval_theta});
cn.contract();

cout<<x<<endl;
cout<<m<<endl;
cout<<y<<endl;
vibes::beginDrawing();

VIBesFigMap fig_map("Map");
fig_map.set_properties(100,100,500,500);
fig_map.axis_limits(0,7,0,7);
fig_map.draw_vehicle(x_truth, 1);
fig_map.draw_box(m, "red");
fig_map.draw_pie(x_truth[0],x_truth[1],interval_rho,interval_theta);
fig_map.draw_box(x.subvector(0,1)); // does not display anything if unbounded

fig_map.show();

vibes::endDrawing();
}