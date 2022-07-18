from deap import algorithms
ﺑ=ImportError
ﷹ=int
𡨖=None
𐳛=range
𣧩=sorted
𐡨=list
𬎆=set
𠰓=len
𥅉=enumerate
𞸹=open
𞸅=print
ڕ=exit
𤀫=slice
𞺛=abs
𩬑=zip
ﲜ=input
𞺂=sum
ۋ=False
颣=str
𐣥=isinstance
𐬪=IndexError
𐦐=float
ﺼ=True
ࡘ=Exception
ﴊ=round
𨑻=map
𐦵=algorithms.eaMuPlusLambda
from deap import base
𦳸=base.Toolbox
𡙌=base.Fitness
from deap import creator
ﴟ=creator.Individual
ꌮ=creator.FitnessMin
𨵩=creator.create
from deap import tools
ﴧ=tools.Statistics
计=tools.HallOfFame
痜=tools.selTournament
𨔞=tools.initRepeat
ฯ=tools.cxOnePoint
𐢖=tools.cxTwoPoint
import json
ꤹ=json.dumps
ﶖ=json.load
import pandas as pd
𦢼=pd.read_excel
import random as rd
딬=rd.uniform
𐦴=rd.random
ن=rd.shuffle
import numpy as np
𮟌=np.mean
𞡔=np.argmax
冰=np.argmin
𐨐=np.ndarray
ࢫ=np.max
𐬬=np.std
呓=np.min
䫮=np.linspace
䊐=np.histogram
𐭢=np.ones_like
ﶶ=np.float32
뜈=np.isfinite
𦻍=np.array
𦽼=np.arange
𫆪=np.random
import math
ﱨ=math.floor
ؿ=math.isnan
import os
짐=os.system
𩴂=os.name
import time
慉=time.sleep
㤠=time.time
import collections
胗=collections.abc
from itertools import repeat
from datetime import datetime
import multiprocessing
炵=multiprocessing.Pool
import pyminifier
try:
 from 胗 import Sequence
except ﺑ:
 from collections import Sequence
if 𩴂=='nt':
 import winsound
𞤟=㤠()
def 譈(freq:ﷹ,duration:ﷹ,𞺂:ﷹ=1)->𡨖:
 for 𞢈 in 𐳛(𞺂):
  if 𩴂=='nt':
   winsound.Beep(freq,duration*1000)
  else:
   짐(f'play -nq -t alsa synth {duration} sine {freq}')
  慉(duration)
ﵦ=𦢼("Function_compatibility_1.xlsx")
ﵦ=ﵦ.set_index('Instances')
㰆=𦢼("Material_cost.xlsx")
㰆=㰆.set_index('Instances')
ﵤ=㰆.to_dict()
𛂾=𦢼("instances_compatibility.xlsx")
𛂾=𛂾.set_index('Instances')
𩎳=𦢼("Required_operations.xlsx")
𩎳=𩎳.set_index('Index')
蘷=𦢼("PrecedenceOperationsMatrix.xlsx")
蘷=蘷.set_index('Operations')
𐡍=𦢼("Machine_compatibility.xlsx")
𐡍=𐡍.set_index('Operations')
ﻞ=𐡍.to_dict('index')
𘝲={k:{a:b for a,b in v.items()if not ؿ(b)}for k,v in ﻞ.items()}
ﴩ=𦢼("Config_change_cost.xlsx")
ﴩ=ﴩ.set_index("Machines")
𞠧=𦢼("Displacement_cost.xlsx")
𞠧=𞠧.set_index("Machines")
𞠧=𞠧.values.tolist()
𞡓=[𞺅 for 𞢈 in 𞠧 for 𞺅 in 𞢈]
𬉏=𣧩(𐡨(𬎆([mod[:2]for mod in 𐡨(𛂾.index)])))
𞸙=𠰓(𬉏)
𤴏=19 
𘧀=𤴏
ﭸ=𐡨(𬎆([w[:2]for w in 𐡨(𐡍.columns)]))
ﭸ=𣧩(ﭸ)
𞠼=[𞢈 for 𞢈,v in 𥅉(ﭸ,1)]
𐢑=𠰓(ﭸ)
ﳻ=[𞢈 for 𞢈,v in 𥅉(ﭸ,1)]
ن(ﳻ)
골=[func for func in ﵦ]
try:
 with 𞸹("selected_functions.json")as function_values:
  僇=ﶖ(function_values)
  𐣤=僇.get('selected_idx')
  ﰚ=僇.get("customer_id")
except FileNotFoundError as identifier:
 𞸅("This requires the file: selected_functions.json")
 ڕ(1)
𞺚=[골[𞢈-1]for 𞢈 in 𐣤]
𛆴=[[inst for inst in 𐡨(𛂾.index)if mod in inst]for mod in 𬉏]
𞸖=4
戈=4
𢿸=𐳛(𞸙)
ﱾ=𐳛(𞸙,𞸙+𤴏)
𞠇=𐳛(𞸙+𤴏,𞸙+2*𤴏)
𐳫=𐳛(𞸙+2*𤴏,𞸙+2*𤴏+𐢑)
𐤸=𤀫(0,𞸙)
ڇ=𤀫(𞸙,𞸙+𤴏)
ﴼ=𤀫(𞸙+𤴏,𞸙+2*𤴏)
ݺ=𤀫(𞸙+2*𤴏,𞸙+2*𤴏+𐢑)
چ=2
昌=[𞢈 for 𞢈 in 𐡍.index]
臠=𞠼
𡬻=1
ࢲ=2
𬵆=1
ﺿ=5
ߕ=1
萩=1
𨵩("FitnessMin",𡙌,weights=(-1.0,))
𨵩("Individual",𐡨,fitness=ꌮ)
def 鍍(float_,𞺂):
 return ﱨ(float_*10**𞺂)/(10**𞺂)
def 𐪅(list_,𞺂):
 缊=[]
 for 䀣 in list_:
  缊.append(ﱨ(䀣*10**𞺂)/(10**𞺂))
 return 缊
def 𝕯(limit,ind,module_inst=𛆴,cost=ﵤ):
 𪰒=0
 𐰁=[]
 for 𞡃 in 𐳛(limit):
  ﶭ=𞺛(ﱨ(ind[𞡃]*𠰓(module_inst[𞡃])))
  𧙶=module_inst[𞡃][ﶭ]
  𐰁.append(𧙶)
  𪰒+=cost['Cost'][𧙶]
 return 𪰒,𐰁 
def 𐼇(ind,ops_machine=ops_machine,part2_slice=part2_slice,part3_slice=part3_slice):
 𧧁=[ﱨ(𠰓(ops_machine.get(𞢈))*m)for 𞢈,m in 𩬑(ind[part2_slice],ind[part3_slice])]
 𐩲={k:ops_machine[k]for k in ind[part2_slice]}
 𩋆=[𠰓(ops_machine.get(𞢈))for 𞢈 in ind[part2_slice]]
 for 𞢈 in 𐳛(𠰓(𧧁)):
  if 𧧁[𞢈]>=𩋆[𞢈]:
   𞸅("ERROR!")
   𞸅(f"decode_wc: {decode_wc}")
   𞸅(f"indiv2: {ind[part2_slice]}")
   𞸅(f"indiv3: {ind[part3_slice]}")
   ﲜ()
 ﯦ=[𐡨(𐩲[op].keys())[𞢈]for op,𞢈 in 𩬑(ind[part2_slice],𧧁)]
 𞤦=𞺂([𐡨(𐩲[op].values())[𞢈]for op,𞢈 in 𩬑(ind[part2_slice],𧧁)])
 return 𞤦,ﯦ
def ﯢ(ﯦ,cost_change_config=cost_change_config):
 𐤤=𣧩(ﯦ,key=lambda x:ﷹ(x[1]))
 𐬤=[]
 for ᔷ,ﺚ in 𩬑(𐤤,𐤤[1:]):
  if cost_change_config[ᔷ][ﺚ]!=1000:
   𐬤.append(cost_change_config[ᔷ][ﺚ])
 𪂻=𞺂(𐬤)
 return 𪂻
def 먵(ind,ﯦ,ݺ):
 𨘣={}
 for 𞢈,k in 𥅉(ind[ݺ],1):
  𨘣[𞢈]=k
 𥚷=[]
 for 𞢈 in 𐳛(𠰓(ﯦ)-1):
  𥚷.append(𞺛(𨘣[ﷹ(ﯦ[𞢈][1])]-𨘣[ﷹ(ﯦ[𞢈+1][1])]))
 𐼘=𞺂([x*چ for x in 𥚷])
 return 𐼘
def ﱶ(ind,ݺ,displacement_cost=displacement_cost):
 ﴟ=[𞺛(𐲮-ip)for 𐲮,ip in 𩬑(ﳻ,ind[ݺ])]
 𞸔=[𞺛(dist)*𞺛(渠)for dist,渠 in 𩬑(ﴟ,displacement_cost)]
 ࠑ=𞺂(𞸔)
 return ࠑ
''' VERIFICAR ESSA FUNCAO DEPOIS DA GET MODULE INSTANCES'''
def 𧻮(icls):
 ﯛ=[鍍(𐦴(),𞸖)for _ in 𢿸]
 𞠺=昌[:]
 ࢠ=𐡨(𫆪.choice(𞠺,19,replace=ۋ))
 𐴣=ࢠ
 ن(𐴣)
 𭅷=[鍍(𐦴(),戈)for _ in 𞠇]
 𭽆=臠[:]
 ن(𭽆)
 𗟕=𭽆
 return icls(ﯛ+𐴣+𭅷+𗟕)
def 𪙻(lsta):
 ﻼ=""
 for 䀣 in lsta:
  ﻼ+=颣(䀣)+"-"
 ﻼ=ﻼ[:-1]
 return ﻼ
def 𤃷(ﳣ,part2_slice=part2_slice):
 螂=0
 𪽯=0
 𐣬=0
 𮤠=0
 𬼒=0
 ﶎ=0
 瓳=0
 濂=0
 ﻼ,𐰁=𝕯(limit=𞸙,ind=ﳣ)
 𬁋=[]
 for 𥛅 in 𐰁:
  𬁋.extend(𐡨(𩎳.query(f'{key} > 0')[𥛅]))
 𐰝=ﳣ[part2_slice]
 𞤦,ﯦ=𐼇(ind=ﳣ)
 𪂻=ﯢ(selected_wc=ﯦ)
 𐼘=먵(ind=ﳣ,selected_wc=ﯦ,part4_slice=ݺ)
 ࠑ=ﱶ(ind=ﳣ,part4_slice=ݺ)
 豂=(ﻼ+𞤦+𪂻+𐼘+ࠑ)
 𐣵=𛂾[𐰁]
 for 𞢈 in 𐰁:
  for 𮅊 in 𐣵:
   if 𐣵[𞢈][𮅊]==0:
    𪽯+=2
 for op in ﳣ[part2_slice]:
  if ﳣ[part2_slice].count(op)>1:
   𐣬+=1
 ﲯ=ﵦ[𞺚]
 𐪇=ﲯ.transpose()
 𬿮=𐪇[𐰁]
 for 𮅊 in 𬿮:
  if(𬿮[f'{col}']==0).all():
   ﶎ+=2
 ﱫ=𬿮.transpose()
 for 𮅊 in ﱫ:
  if(ﱫ[f'{col}']==0).all():
   𬼒+=2
 '''
    if collections.Counter(req_ops) != collections.Counter(ops_sequence):
        op_not_required += 1
    ''' 
 냜=𐡨(𬎆(𬁋)-𬎆(𐰝))
 瓳=𠰓(냜)
 for i1,op1 in 𥅉(ﳣ[part2_slice]):
  for i2,op2 in 𥅉(ﳣ[part2_slice]):
   if 蘷[op1][op2]==1 and i2<i1:
    濂+=1
 螂=(+𪽯*𡬻+𬼒*ࢲ+ﶎ*𬵆+𐣬*萩+瓳*ﺿ+濂*ߕ)
 return((豂)/199+螂,)
'''
# def cxTwoPointCopy(ind1, ind2):
#   size = len(ind1[part2_slice])
#   cxpoint1 = random.randint(1, size)
#   cxpoint2 = random.randint(1, size - 1)
#   if cxpoint2 >= cxpoint1:
#       cxpoint2 += 1
#   else: # Swap the two cx points
#       cxpoint1, cxpoint2 = cxpoint2, cxpoint1
#
#   ind1[cxpoint1:cxpoint2], ind2[cxpoint1:cxpoint2]
#       = ind2[cxpoint1:cxpoint2].copy(), ind1[cxpoint1:cxpoint2].copy()
#
#   return ind1, ind2
'''
def 𨣜(ﳣ):
 for 𞢈 in 𐳛(𠰓(ﳣ)):
  if ﳣ.count(ﳣ[𞢈])>1:
   ﻠ=[val for val in 昌 if val not in ﳣ]
   ﳣ[𞢈]=𫆪.choice(ﻠ,1)[0]
 return ﳣ
def 𞢒(𭊌,𘛳):
 𭊌,𘛳=𐢖(𭊌,𘛳)
 𭊌=𨣜(𭊌)
 𘛳=𨣜(𘛳)
 return 𭊌,𘛳
def 𐩼(ﳣ):
 for 𞢈 in 𐳛(𠰓(ﳣ)):
  if ﳣ.count(ﳣ[𞢈])>1:
   ﻠ=[val for val in 臠 if val not in ﳣ]
   ﳣ[𞢈]=𫆪.choice(ﻠ,1)[0]
 return ﳣ
def 刋(𭊌,𘛳):
 𭊌,𘛳=𐢖(𭊌,𘛳)
 𭊌=𐩼(𭊌)
 𘛳=𐩼(𘛳)
 return 𭊌,𘛳
def ޣ(𭊌,𘛳,eta=20,low=0,up=1):
 𭊌[𐤸],𘛳[𐤸]=ฯ(𭊌[𐤸],𘛳[𐤸])
 𭊌[𐤸],𘛳[𐤸]=𐪅(𭊌[𐤸],𞸖),𐪅(𘛳[𐤸],𞸖)
 𭊌[ڇ],𘛳[ڇ]=𞢒(𭊌[ڇ],𘛳[ڇ])
 𭊌[ﴼ],𘛳[ﴼ]=ฯ(𭊌[ﴼ],𘛳[ﴼ])
 𭊌[ﴼ],𘛳[ﴼ]=𐪅(𭊌[ﴼ],戈),𐪅(𘛳[ﴼ],戈)
 𭊌[ݺ],𘛳[ݺ]=刋(𭊌[ݺ],𘛳[ݺ])
 return 𭊌,𘛳
def 홣(ﳣ,p=𡨖):
 𞢈,𞺅=𫆪.choice(𦽼(𠰓(ﳣ)),2)
 ﳣ[𞢈],ﳣ[𞺅]=ﳣ[𞺅],ﳣ[𞢈]
 return ﳣ,
def שּ(ﳣ,𐨨,ﰣ,indpb):
 ܙ=𠰓(ﳣ)
 if not 𐣥(𐨨,Sequence):
  𐨨=repeat(𐨨,ܙ)
 elif 𠰓(𐨨)<ܙ:
  raise 𐬪("low must be at least the size of individual: %d < %d"%(𠰓(𐨨),ܙ))
 if not 𐣥(ﰣ,Sequence):
  ﰣ=repeat(ﰣ,ܙ)
 elif 𠰓(ﰣ)<ܙ:
  raise 𐬪("up must be at least the size of individual: %d < %d"%(𠰓(ﰣ),ܙ))
 for 𞢈,xl,xu in 𩬑(𐳛(ܙ),𐨨,ﰣ):
  if 𐦴()<=indpb:
   ﳣ[𞢈]=딬(xl,xu)
 return ﳣ,
def ﱶ(ﳣ,indpb_bin=0.05,indpb_real=0.05,low=0,up=1):
 ﳣ[𐤸]=שּ(ﳣ[𐤸],low=low,up=up,indpb=indpb_real)[0]
 ﳣ[𐤸]=𐪅(ﳣ[𐤸],𞸖)
 ﳣ[ڇ]=홣(ﳣ[ڇ])[0]
 ﳣ[ﴼ]=שּ(ﳣ[ﴼ],low=low,up=up,indpb=indpb_real)[0]
 ﳣ[ﴼ]=𐪅(ﳣ[ﴼ],戈)
 ﳣ[ݺ]=홣(ﳣ[ݺ])[0]
 return(ﳣ,)
def 𦻇(init_pop,𫽅,𠱬,ﭔ):
 퉯,ﵽ,𢹽,蟡,寓=ﭔ.select("gen","avg","min","max","std")
 import matplotlib
 matplotlib.rcParams.update({'font.size':7})
 import matplotlib.pyplot as plt
 from scipy import stats
 def ཅ(ﺋ,ꀎ,c='b'):
  ꀎ=𦻍(ꀎ)
  ײַ=뜈(ꀎ)&뜈(ꀎ)
  ꀎ=𐡨(ꀎ[ײַ].astype(ﶶ))
  try:
   𞺂,𥾅,녆=ﺋ.hist(ꀎ,histtype='stepfilled',bins=40,color=c,alpha=0.2,weights=𐭢(ꀎ)/𐦐(𠰓(ꀎ)))
   𞺂,𐫡=䊐(ꀎ,bins=40,density=ﺼ)
   𐤑=1./𐦐(𞺂.𞺂())
   𦾴=䫮(呓(ꀎ)-0.*𐬬(ꀎ),ࢫ(ꀎ)+𐬬(ꀎ),1000)
   𗥸=stats.gaussian_kde(ꀎ,bw_method=0.125).evaluate(𦾴)
   ﺋ.plot(𦾴,𗥸*𐤑,c=c,alpha=0.3,lw=0.6)
  except ࡘ as e:
   𞸅(e)
 def 𭴇(ﺋ,title='Title'):
  놀,𞹱=.25,.5
  𐴉,ꋾ=.25,.5
  𧦽=놀+𞹱
  𨄼=𐴉+ꋾ
  ﺋ.text(0.5*(놀+𧦽),0.5*(𐴉+𨄼),title,horizontalalignment='center',fontsize=6,color='k',alpha=1.0,zorder=2,transform=ﺋ.transAxes)
 禑=plt.figure(figsize=(10,5),dpi=150)
 𬱑=plt.subplot2grid((2,5),(0,0),rowspan=1,colspan=2)
 𥘪=𬱑.plot(퉯,𢹽,"b-",label="Minimum Fitness",lw=0.75)
 ހ=𬱑.plot(퉯,ﵽ,"g-",label="Average Fitness",lw=0.75)
 𞢨=𬱑.plot(퉯,蟡,"r-",label="Maximum Fitness",lw=0.75)
 𬱑.set_xlabel("Generation")
 𬱑.set_ylabel("Fitness")
 𬱑.grid(alpha=0.5)
 𬱑.legend(loc="upper right")
 𤙿=plt.subplot2grid((2,5),(1,0),rowspan=1,colspan=2)
 𤁦=𤙿.plot(퉯,寓,"r-",label="Fitness STD",lw=0.75)
 𬱑.set_xlabel("Generation")
 𤙿.set_ylabel("Fitness STD")
 𤙿.grid(alpha=0.5)
 𤙿.legend(loc="upper right")
 髐=plt.subplot2grid((2,5),(1,2),rowspan=1,colspan=1)
 ཅ(髐,𐨐.flatten(𦻍([𦻍(ind[:3])for ind in 𫽅])))
 髐.grid(alpha=0.5)
 髐.set_ylabel('Probability in Pop')
 髐.set_xlabel('Part1 Values')
 𠶏=plt.subplot2grid((2,5),(1,3),rowspan=1,colspan=1)
 ཅ(𠶏,𐨐.flatten(𦻍([𦻍(ind[ﴼ])for ind in 𫽅])))
 𠶏.grid(alpha=0.5)
 𠶏.set_ylabel('Probability in Pop')
 𠶏.set_xlabel('Part3 Values')
 ݐ=plt.subplot2grid((2,5),(1,4),rowspan=1,colspan=1)
 𥷮=𦻍([𦻍(ind[ڇ])for ind in 𫽅])
 ﱪ=ݐ.imshow(𥷮,interpolation='nearest')
 ݐ.set_aspect('auto')
 ޘ=plt.colorbar(ﱪ,ax=ax5)
 ޘ.ax.tick_params(labelsize=6)
 ݐ.set_ylabel('Individual ID')
 ݐ.set_xlabel('Part2 - Gene Index')
 ﲲ=plt.subplot2grid((2,5),(0,2),rowspan=1,colspan=3)
 ﲲ.set_axis_off()
 妫=init_pop[冰([ind.fitness.values[0]for ind in init_pop])]
 ﮖ=妫.fitness.values[0]
 妫=[ﴊ(𞢈,3)if 𐣥(𞢈,𐦐)else 𞢈 for 𞢈 in 妫]
 𐳮=init_pop[𞡔([ind.fitness.values[0]for ind in init_pop])]
 𫛝=𐳮.fitness.values[0]
 𐳮=[ﴊ(𞢈,3)if 𐣥(𞢈,𐦐)else 𞢈 for 𞢈 in 𐳮]
 鿢=[ﴊ(𞢈,3)if 𐣥(𞢈,𐦐)else 𞢈 for 𞢈 in 𠱬[0]]
 𭴇(ﲲ,'Initial Pop-Best,  fitness = %f'%(ﮖ)+'\n'+颣(妫).replace('[','').replace(']','')+'\n\n'+'Initial Pop-Worst,  fitness = %f'%(𫛝)+'\n'+颣(𐳮).replace('[','').replace(']','')+'\n\n\n\n\n'+'Hof[0],  fitness = %f\n'%(𠱬[0].fitness.values[0])+颣(鿢).replace('[','').replace(']',''))
 plt.tight_layout()
 plt.savefig(f"Results_{str(datetime.now()).replace(':', ' ')}.png")
 plt.show(block=ۋ)
if __name__=="__main__":
 ﳀ=80
 ﹺ=150
 𔖸=2*ﹺ
 殺=0.7
 삦=0.3
 ﺠ=𦳸()
 ﺠ.register("individual",𧻮,ﴟ)
 ﺠ.register("population",𨔞,𐡨,ﺠ.individual)
 ﺠ.register("mate",ޣ) 
 ﺠ.register("mutate",ﱶ) 
 ﺠ.register("select",痜,tournsize=3)
 ﺠ.register("evaluate",𤃷)
 ﺤ=炵()
 ﺠ.register("map",ﺤ.𨑻)
 𫽅=ﺠ.population(n=MU)
 𠱬=计(1)
 𩩹=𫽅[:]
 ࡍ=ﴧ(lambda ind:ind.fitness.values)
 stats.register("avg",𮟌,axis=0)
 stats.register("std",𐬬,axis=0)
 stats.register("min",呓,axis=0)
 stats.register("max",ࢫ,axis=0)
 𫽅,ﭔ=𐦵(𫽅,ﺠ,halloffame=hof,mu=MU,lambda_=LAMBDA,cxpb=CXPB,mutpb=MUTPB,ngen=NGEN,stats=stats)
 𞸅("\nBest INITIAL Individual is : %s"%颣((𩩹[冰([ind.fitness.values[0]for ind in 𩩹])])))
 𞸅("")
 𞸅(f"Best FINAL Individual is : {(hof[0])}")
 𦶙,𐰁=𝕯(limit=nb_modules,ind=hof[0])
 𦶙=ﴊ(𦶙,2)
 𬁋=[]
 for 𥛅 in 𐰁:
  𬁋.extend(𐡨(𩎳.query(f'{key} > 0')[𥛅]))
 頓,ﯦ=𐼇(ind=hof[0])
 𐰝=𠱬[0][ڇ]
 𐰝=𐡨(𨑻(颣,𐰝))
 ﷀ=𐡨(𨑻((lambda x:'OP'+x),𐰝))
 ٲ=ﯢ(selected_wc=selected_wc)
 ٲ=ﴊ(ٲ,2)
 𫳚=먵(ind=hof[0],selected_wc=selected_wc,part4_slice=part4_slice)
 𫳚=ﴊ(𫳚,2)
 𐰥=ﱶ(ind=hof[0],part4_slice=part4_slice)
 𐰥=ﴊ(𐰥,2)
 ᔷ=𠱬[0][44]
 ﺚ=𠱬[0][45]
 𐠰=𠱬[0][46]
 𪣩=𠱬[0][47]
 ߙ=𠱬[0][48]
 𞺎=[ᔷ,ﺚ,𐠰,𪣩,ߙ]
 ﲟ=(𦶙+頓+ٲ+𫳚+𐰥)
 ﲟ=ﴊ(ﲟ,2)
 𐳨={"customer_id":ﰚ,"selected_idx":𞺚,"total_cost":ﲟ,"selected_module_instances":𐰁,"operations_sequence":ﷀ,"process_plan":ﯦ,"layout_design":𐡨(𨑻(ﷹ,𠱬[0][ݺ]))}
 𞹩=(f"OptimalSolution_Customer_{str(customer_id)}.json")
 𞡦=ꤹ(𐳨)
 with 𞸹(𞹩,'w')as 𐲮:
  𐲮.write(𞡦)
 ﳔ=㤠()
 𞸅()
 𞸅(f"Time spent (seconds): {end-start}")
# Created by pyminifier (https://github.com/liftoff/pyminifier)
