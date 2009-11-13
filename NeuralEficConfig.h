const float NeuralEfic::threshold = 302.e-3;
const unsigned NODESVECTOR[]= { 100,10,1}; 
const float WEIGHTVECTOR[]={-1.536279703561886e+00,-3.129024889257820e+00,-8.948033732480555e+00,-8.740323591833662e-01,9.268721015914992e-01,3.021830631256887e-01,-3.721074749123360e+01,1.382149842187985e+00,9.956532909909147e-02,2.028691889832110e-01,8.606724535827469e-01,3.054107274751192e+01,3.570505991374889e+01,1.835115016680202e+01,1.096089354967125e+02,-1.491779752179568e+00,-1.521678072072518e+02,5.098792776787909e+00,7.962962511355790e+00,4.665163320385172e+00,2.541188479003139e+00,-9.751199364017443e+00,4.052964768501642e+00,3.503556466469670e+00,1.278459231735660e+00,-1.416249086015370e+02,-2.564945891212794e+00,4.303185407585466e+00,-3.129298580308934e+00,2.692699281695634e+00,-1.318576693182619e+00,3.952912615539408e+00,-3.904059672247981e+02,5.571286804192690e-01,5.204707136304523e-02,3.546352550815732e+00,5.966457455328291e+00,-4.253247922819706e-01,4.497313425696873e+00,-4.342546390423802e+00,-5.903093906329654e+00,6.109328096738522e-02,1.672899806352809e+00,3.384512521160008e+00,-3.229951522528014e+02,-2.514866014769523e+00,-2.190686703721558e+01,-2.004614528705744e+01,-2.657153106566434e+00,5.703297030896303e+00,-6.097693845355608e-01,1.304905177845818e+00,-1.209859163019182e+00,5.613774189620367e+00,3.066346483297945e+00,3.622756015778278e+00,3.209915801757434e+00,-4.301083635425990e+00,3.873147762653707e+00,6.913080363617814e+00,-9.489577234072808e+00,-5.679332074976251e+01,-2.204176410378917e+00,8.126234930895480e-01,9.414976289272291e+00,1.240598428684220e+01,-7.360028970184156e+00,9.534750518076698e-01,-1.806931281987534e+00,-3.337085196467406e+00,8.873956547217710e-01,-4.459484296319929e+00,1.512877632144524e+00,9.670523187016250e-01,2.618252201501348e+00,1.315388923106045e-01,-1.108831410551399e+01,9.427183315320102e-01,-4.733696060660252e-01,-1.291671728640140e+00,1.804638086189338e+01,-1.934119812630849e-01,3.035930866019129e+00,-1.264718965830325e+00,2.128608961233827e+00,-4.517098598163523e+02,-1.656313911150743e+00,4.852722540897230e+01,1.557150669750226e+00,-1.082483663249334e+00,-9.225338146372700e-01,6.675460301463016e-01,7.127971443441024e-01,-4.204014926321288e-01,-6.340250546248528e-02,-3.000869529319852e-01,-3.396977751645741e-01,-1.984080517360810e+01,-2.213523597620681e-01,-3.892936732556054e-01,-3.084523863198372e-01,2.715573184789210e-01,1.058407154844936e-01,4.473385778319366e+00,3.670407202209460e+00,3.486529074711226e+00,5.593503418246171e+00,5.189345908338965e+00,6.092449011421226e-01,-4.182007177519128e-01,-1.059329847230667e+00,7.281848853344216e-01,-6.055313731477352e-02,4.032570481666345e+00,2.934468744071510e+00,9.085679005418505e+00,8.716840298752617e+00,-1.746882380710622e+00,7.548658490910741e+00,5.322552990915728e+00,1.264960986620738e+01,-1.683861360418533e+01,2.777033462497667e+00,1.255204709685578e+00,2.505399468996699e+01,1.542021877349755e+01,2.988598711415261e+00,1.206897784764241e+01,8.630091384576755e+00,-5.397683318488502e+00,9.165559491767517e+00,9.418646581789059e+00,8.519855525976705e+00,4.009231918212882e+00,3.102919853534154e+00,5.549014432527646e+00,6.972611348550414e+00,1.241084000653611e+01,9.584241221994981e+00,4.314057888857304e+00,6.923108821836408e+00,1.000059081005693e+01,2.608005372906463e+00,7.932720257616308e-02,-8.163698389078684e-01,9.885486677106996e+00,1.315274402293052e+01,1.211130759575707e+01,8.426304475103899e+00,1.996261622431616e+00,-3.677480403622026e+00,9.157488176091062e+00,4.550985306344320e+00,3.918654380463360e+00,4.429536736197784e+00,4.431987837718951e+00,2.656445559188904e+00,4.683137474791375e+00,-2.701856652721288e+01,1.198098030292513e+01,-3.702946964241359e+00,5.943640243879441e+00,4.238612650412092e+00,2.959467111578377e+00,4.816809324742286e+00,1.611927557527220e+01,2.626990314794429e+00,-2.880269254618802e+00,2.992748023287600e+00,-2.081118716574040e-01,4.961464064395888e+00,7.511183533745066e+00,1.117931972742824e-01,-3.947337955918362e-01,8.949790783019715e-01,1.648924715155725e+00,6.252326879790718e+00,4.385346489941483e+00,3.849044927774752e+00,5.429841785881593e+00,6.080976235706456e+00,1.785796862174583e+00,1.591286787118689e+01,5.910966582526878e+00,7.955400322797277e+00,1.708660709747655e+01,5.727789750908788e+00,7.113097405930581e+01,4.459642425256227e+00,6.318788511757837e+00,3.312548431020446e+00,1.807091465550200e+00,5.112356895142043e+00,3.335319913756057e+00,4.699731523390454e+00,3.838244373948791e+00,-7.199938879962521e-02,-3.206601527999585e-01,-1.091056084211078e+00,-2.729496594127464e-01,7.025172339852651e-01,-6.114104389994869e-01,-8.324114471633243e-01,-5.587982237752020e+00,1.769851817191227e+00,-4.375562291938015e+00,-5.716780101608405e+00,7.832627300598717e+00,1.620230932609495e-01,2.425473946739437e+00,-2.242178435092332e-01,-4.767644445034704e+00,1.662952650330866e+00,-5.606592012189524e+00,1.807504361536070e+00,-2.496673350504698e+00,-5.405948159353485e+00,-4.216789720099620e-01,-8.936701840666203e+00,7.643663372270859e-01,-1.075408018782971e+01,1.401743135340812e+02,-8.485844493330601e+00,-8.501186410195482e+00,-1.003617021746288e+01,-1.099740080838626e+01,-9.068598561746427e+00,-1.276262726843606e+01,-4.999934575339264e+00,1.798915991066664e+00,7.470821691993020e+00,-1.438449401796574e+01,-2.521274504495858e+00,-8.370370973036126e+00,-9.803500030333716e+00,-5.211918579346149e+00,-3.870990912080227e+00,-6.169154803159180e+00,-3.122114072779382e+00,-1.018906397731510e+01,-4.140532874982237e+00,-1.235411375336569e+01,-4.219282121938210e+00,-2.966334905069106e+00,4.807468532187138e+00,-9.294179468990574e+00,-8.673712956765907e+00,-1.272027109502614e+01,-1.658893652652769e+00,6.909845171689767e+00,6.260568691274796e+00,-4.626528300555825e+00,9.461392006240720e-01,5.994020844380300e-01,-1.196079321863828e+02,-9.833517470201228e+00,7.709954951768727e+01,-4.088611811998160e+00,-1.212137530428969e+01,-5.067758217444106e+00,3.911039021750542e+00,-9.161322851121481e+00,-2.364297835682644e+00,-1.579711335173758e+01,6.994917384399857e+00,-4.877235016798458e+00,1.270757279771420e+00,-9.295125426188720e+00,-6.552846332762628e+00,-2.217998761509612e+01,-4.792333291200796e+00,3.788295411785841e+00,-1.240986209891787e-01,-3.289373813077779e-01,-1.463573565846511e+00,-8.204923780576815e+00,-6.745528320344436e+00,-4.099254313683682e+00,-4.523831570557686e+00,-2.913340666531770e+00,-5.122029841517699e+00,-1.676306088631395e+00,-1.608805790061188e+01,-7.183844926751915e+00,-3.590217160802176e+00,-8.526330077208134e+01,-1.149848582662925e+01,5.093476052210257e+02,-8.158122630975411e+00,-6.077823099043371e+00,-4.364409063513964e+00,1.386846144592185e+01,-4.911432471659200e+00,-4.740689150175923e+00,-2.603691764522341e+00,-5.153550906902352e+00,-6.828071429071064e-01,-1.400353947874317e+00,1.867712852778583e+00,-2.604701399605285e-01,2.104342532730360e+00,6.103309001177835e+00,-6.159310430712524e-02,-1.685183326477722e+00,-1.857077404462629e+00,-1.793498145746829e+00,-4.002523328184824e+00,-3.844782141499546e+00,1.927021625894191e+00,1.776413671301088e+00,1.389368649863788e+00,1.429737526409759e-01,-2.635984176165353e+00,-2.808489247551884e+00,-4.265222481819877e-01,2.379302989228599e+00,-1.629292344839278e+00,-6.199815584672301e+00,-9.483968868967041e+00,-2.247700268400291e+00,1.907945717945511e+00,-4.131476029953562e+00,-5.916828958552076e-01,-3.654744542634406e+00,-3.300199412298649e+00,-3.810504772539551e+00,-7.958150413730281e-01,-3.106575996868228e+00,-8.374281929097268e-01,-1.161736446778048e+01,-4.898764626062350e+00,-1.450958438808082e+01,-3.079548587540685e+00,1.183775137056466e+00,-3.996993122841099e+00,-4.196677270559233e+00,2.295490663507988e+00,-4.101296567745600e+00,-1.327086161702494e+01,7.753711940773250e+00,-6.177697000420991e+00,-1.681707922286937e+00,-1.853866292978563e+00,-2.753584041192455e+00,-7.185240803430041e+00,-9.029744126050307e+00,-2.885095608335158e+00,-9.712499725655709e+00,-5.517564738730533e+00,-1.958277661110303e+00,2.076591624849431e+00,-4.623522357920521e+00,9.287422698105072e+00,-8.497355204891363e+00,-8.960063277134566e+00,-7.737850509045640e+00,-2.178266340425766e+00,-1.105986943465937e+01,-1.019899815546619e+01,-8.588958084395992e+00,-4.348766380352136e+00,-1.143165838757294e+01,-4.537225862413593e+00,-2.004584286939691e+01,3.175787281716159e+00,3.935813877001417e+00,-8.739486637975018e+00,1.277776592422745e+00,-4.696416220868813e+00,-1.029809960998926e+01,-2.963689024455732e+00,-1.594379079246105e+01,-8.888569980163995e-02,6.247875097046333e-01,-6.219623197409074e-01,-2.277073475273996e+00,-1.661220652433749e+00,-8.590637693380199e-01,8.315472315833352e+00,-2.563356226293802e+00,-1.887187068351318e+00,-7.765308268117617e-01,-2.257461446194808e+00,-3.524656145333870e+00,-6.645847514776714e+00,-5.382286434414225e+00,-1.367557141546585e+00,1.979032162529652e+00,-7.324879508814309e+00,-3.828419938552814e+00,-1.477927266068839e+00,-3.968532004253816e+00,-4.246961189259281e+00,3.164413422318213e-01,-1.978469093995332e+00,-5.564261302799800e+00,7.373526479912648e-01,6.067355485690331e-01,-2.556280180925254e-01,4.537796461078724e+00,3.074405672070553e+00,1.492645365721915e+00,-1.530117730785619e+00,-1.586477807684343e+00,-3.340184363214958e-01,-3.133285870522763e-02,-2.814998592460589e+00,-1.611778228899934e+00,3.493236260191546e+00,2.844698504722428e+00,1.081513284426187e+00,-3.667591402533966e-01,-2.667475224471324e+00,-1.003359403636998e+00,-2.440939039231153e+00,-3.816237994317099e+00,-1.649873227195451e+00,1.299475383620674e+00,-7.868367074564514e+00,-2.553215023294861e+00,-3.111493318697694e+00,-1.575787661775456e+01,-1.768042844766152e+00,-8.604265957803802e+00,-3.863399609615726e+00,-1.074950331044386e+00,-6.435477281725758e+00,1.213210011448794e+00,-6.488447113658808e+00,-4.161712920719510e-02,-1.150317368158515e+00,-6.778230019950014e+00,-5.138412794787262e+00,-4.875737771873591e-01,-8.974901810027127e-01,-8.558674731663091e+00,-7.079643702760635e+00,-3.203392718437922e+00,1.573318106080581e+00,3.844789055643746e-02,-5.650919140023839e+00,5.153192283107885e-01,-2.016060701522798e+00,-1.917545430384862e+00,-1.752217010146014e+00,-5.723825390606232e+00,-1.499038829532984e+00,-8.938146548412709e+00,-7.155543131885859e+00,4.927737543041129e-01,-3.201228100712185e+00,-6.311916082726989e+00,5.991166493461425e+00,-4.897826043497804e+00,3.254716003746571e+00,-4.566849025719175e+00,5.511215073554269e+00,2.557262053655052e+00,-5.117581075886356e+00,1.114186481440491e+00,-4.491528111573154e+00,5.252629179029427e+00,2.266527388284616e+00,6.537524872291836e+00,-1.342133077803918e+01,-3.537382982101496e+00,4.892364751911146e-01,4.828501441932538e+00,-3.214660348053926e+00,-4.955494949803389e-01,1.043401514421496e+00,-2.449790790672396e+00,4.628166166555862e-01,2.626846005642609e-01,1.207639860708900e-01,4.684497869135582e-01,-2.712772659473203e+00,-1.415751772689764e+00,-1.242924001338021e+00,-2.412302777008698e+00,-9.929459250980252e-01,-9.604222314447216e-01,-2.822711283805751e+00,9.509444495881693e-01,-2.728366799349049e+00,-1.736831108580845e+00,-1.698883499424573e+00,-1.173351893032780e+00,-3.928405801771819e+00,-1.572856185861142e+00,-2.120392222173948e+00,-1.731829182120571e+00,-7.728625535942598e-01,-7.747496751018823e-01,2.642850477319790e-01,1.378179139870660e+00,8.687541733917634e-01,4.014177774606990e-01,4.230326633934277e-01,1.982061066217246e-01,-8.245506931145411e+02,-2.824798324105510e+01,-2.172107109310284e+00,-3.064229262747004e+00,-1.661109442285282e+00,-9.223394280145300e+00,5.788683122658558e+01,-3.137283206413350e+00,5.032198963414759e+00,8.475901213673476e+00,4.511336831164383e+00,1.511711729504759e+00,3.079307157897966e+00,7.158082955458191e+00,8.975832163877280e-01,1.319177087008635e+01,-2.374338190874559e+00,-3.602543765100377e+01,-7.074926986672551e+00,-2.148073536474086e+01,-4.974205013201104e+00,-1.346219282154986e+01,-3.963307427726326e+00,2.871210259684327e+01,-4.254808975017603e+01,3.148502103008973e+00,-1.146932308226140e+00,-2.057437270522819e+01,-7.235747394339656e+00,-6.351883119797355e+00,-4.701248183823463e+00,-1.093876270905093e+01,7.484649394766167e+01,-5.713879311197954e-01,-8.952191387787241e+00,-1.094321694470106e+01,-8.468755852371084e+00,-7.333178922036895e+00,-9.493741006388989e+00,4.872115648561542e+00,-1.148299905577527e+00,-1.339006369390854e+01,-2.521409979338938e+01,-6.248246059274934e+00,-7.892588870394654e+00,-6.842815926569000e+00,-9.263936283279588e+00,-2.153458973313152e+01,-8.027024617081800e+00,-8.611316159690933e+00,1.068025697631357e+00,-8.170100375318269e+00,2.729452816116551e-01,-3.013245389612625e+00,-9.661605298662664e+00,-9.288530414129953e+00,-6.569451935476474e+01,-1.204834842405069e+01,-6.719368601014810e+00,2.195423334982677e+01,-1.146508566647280e+01,-1.919743004346278e+00,-7.742933020175305e+00,-5.450572900618774e+00,-1.211576737130028e+01,-1.696263241999700e+01,-6.396491256549348e+00,-1.561094117248987e+01,-1.057023305665984e+00,-7.739168661236391e+00,-3.400877476254437e+00,-6.890559961865415e+00,9.708031604840102e-01,9.990671010474728e-01,1.492001163209254e-02,-2.360910753199396e+00,-1.071792381079151e+00,-5.055213414007659e+00,-4.966478662248957e+00,-4.801620748458790e+00,1.519072708111756e+01,2.004376859406455e+01,-7.357634345851173e+00,2.979806309990210e+00,-6.800091541908802e+00,-5.452129996122921e-01,8.747134135578095e-02,-3.668825673196644e+01,-7.243144339404632e+00,1.694458826183701e+00,-3.237194089879305e+00,-8.904020247432916e+00,-5.187165856454046e+00,-2.494601936348845e+00,4.795579637419763e-01,-2.396303681669612e+00,-1.818856324032827e+01,4.288146498050379e-01,-5.458022283988850e+00,2.442289927351726e+00,2.372304756327083e-01,1.931058873197484e+00,-1.412094459558804e+01,-3.895109203452922e+00,-3.117436161331854e+00,-3.562029801869871e+00,-5.706404883142624e+00,-4.298056826242966e+00,-5.828871940508582e-01,7.634186334522816e-01,-1.632439181127091e+00,-1.918110348514840e+00,1.606029611842883e+00,-4.166230346319010e+00,-2.292918977154380e+00,-1.086278255387011e+01,-2.605887249992485e+00,-9.211462720186978e+00,-6.286423455526649e+00,-4.998549335632782e+00,-4.257057926770403e+00,-1.255017464870106e+01,-1.013504865812305e+01,-8.754137834380003e+00,-1.716880661415261e+01,-1.092407803596015e+01,-1.027879363079705e+01,-1.349661461250480e+01,-5.018470192156893e+00,-1.340608003269649e+01,-1.005185369908639e+01,-1.603010414413705e+01,-2.294545023904298e+00,-5.691588127314467e+00,-5.335431514966930e+00,-1.241910226743806e+01,-7.245321035602059e+00,-1.536651939982037e+01,-1.465634988238201e+01,-7.487820431106473e+00,-9.764342142419226e+00,-5.238827890220179e+00,-6.315689895818612e+00,-5.259120340618004e+00,-5.470801643784624e-02,-5.419359008161607e+00,-4.477316349299801e+00,-6.833260981207964e+00,-1.019370910876728e+01,-8.903160931851062e+00,5.374385589729618e+00,-1.298752101156241e+00,-4.565296222700937e+00,-9.770443398908485e+00,-7.313097014193164e+00,-8.901617210909400e+00,-1.325643181831378e+01,-1.090415962117355e+01,-3.761159270453974e+00,-3.945622864930858e+00,-1.218294019958031e+01,-6.597241974384742e-02,-8.393815337831803e+00,-1.099204347297031e+01,2.572894807128493e+00,-1.318323513649495e+01,8.491636925484665e-01,-3.690827301188853e+00,-6.807397423452917e+00,-9.716944419229204e+00,-5.247180159327282e+00,4.018693749891641e+00,7.723012632783663e-02,-3.595998861348731e-01,-1.970534804859477e+00,-2.960356540767314e+00,-2.190494932850916e+00,-3.303590919515354e+00,-4.099403876990931e+00,-4.597342242652453e+00,-6.156590188675707e+00,-9.251950314666800e-01,-9.025288812131011e+00,-3.568675089612297e+00,-6.429718782082987e+00,-6.608881746820849e+00,-3.731807352583989e+00,-1.116701663663774e+01,-7.974774629008739e+00,-3.802232798229218e+00,-3.155725762875695e+00,-3.929706522761317e+00,-5.312357539437886e+00,-3.893396758010370e+00,-1.666662355504514e+00,-5.001812777052975e+00,2.079863685297044e-01,-3.314343502047654e-01,2.988950483899583e-01,2.910907778374741e-01,-4.170167565907161e-01,-5.079439708155078e-01,5.027658486897914e+00,5.566457557559807e+00,3.171214724447054e+00,3.486812726045213e+00,5.293677233584920e+00,4.421711968673883e+00,-1.262111153839742e+00,-2.530190463144493e-01,-1.539024342350961e+00,2.430007661541350e+00,2.441489106741726e+00,-1.557750378887362e-01,6.511700840047357e+00,1.237752713935954e+01,2.352343396730783e+00,1.459544310706569e+01,1.420871812461376e+01,5.228889000031842e+00,5.306488481330838e+00,9.170773628142213e+00,4.854156252774312e+00,1.353366488524470e+01,1.698523100934183e+01,6.840053618084309e+00,9.051862195495605e+00,6.426492737232350e+00,1.154132421100976e+01,1.298230862196485e+01,5.653544248361221e+00,1.620761969591472e+01,7.677006976402228e+00,4.780131318916900e+00,7.109086673031006e+00,9.545030787680947e+00,3.434837007606290e+00,1.289920267653732e+01,4.226269978075694e+00,7.524912005267804e+00,4.635015892725125e+00,1.413792446796034e+01,4.842137154746976e+00,7.161309180186223e+00,6.321670955978821e+00,1.158926235526583e+01,-4.963504908040378e-01,9.098571701778857e+00,3.913316883849467e+00,-1.468425899201324e+00,-5.840683263512165e+00,8.784519436025674e+00,-5.797877994581763e+00,6.070027547830616e+00,5.425326828489093e+00,4.253958240776353e+00,8.758539553762111e+00,1.176053829747283e+01,2.545832543180008e+00,2.693060995764250e+01,-2.453225300828667e+00,7.773152069371379e+00,-4.834745562503761e-01,1.276798382257325e+00,3.105398515589109e+00,8.065247995981339e-01,1.700619178863699e+01,1.195652421256928e+01,4.024812810105698e+00,8.341188988190954e+00,1.061256687621869e+01,1.056834534462181e+01,-1.701195878190644e-01,-6.379794998431952e-02,8.074351300563472e-01,8.548981179943903e-01,1.450735916090156e+00,5.691100206707759e+00,3.539952544015534e+00,4.953863074659333e+00,2.309630250577634e+00,1.270898665066276e+00,9.765836298296088e+00,3.549582582361241e+00,3.074031916426223e+00,1.953823269613178e+00,5.765985332301196e+00,6.324212574518260e+00,8.990955527355174e+00,3.656923945473206e+00,4.009946131045141e+00,4.964724599570008e+00,4.913028450951331e+00,3.400541800277459e+00,3.085384145424602e+00,1.431927983620283e+00,8.141741573117370e-01,8.257648434702241e-01,-5.377821165760602e-01,-2.310941709687212e-01,8.461678445022461e-01,4.798951314400474e+00,-6.667563640767774e+00,-5.250777188318302e+00,-2.144768383964740e+00,-3.812635854020646e+00,-5.112953145752136e+00,-3.561290704936587e+00,1.313457168863877e+00,-5.623727317797460e-01,1.023289955281504e+00,-1.367360952243166e+01,-3.375856164972638e+00,-2.525902794252237e+00,7.085492338280273e+00,-1.941892787242683e-01,-4.829480519591549e-01,-1.035435059808175e+01,-1.361658070377321e+01,-3.662233563201461e+00,-7.178504573124622e+00,-3.398265558229939e-01,1.137580532670010e+01,-9.980994231297466e+00,-6.714473999925967e+00,-1.529051363569708e+01,-6.575219488677114e+00,-7.336785795740537e+00,-5.112899074904508e+00,-1.168142867369386e+01,-6.645208812563007e+00,-1.188146081597677e+01,-7.504948993359240e+00,2.234442937258334e+01,-8.099958581027927e+00,-1.378587248341627e+01,-8.523629866756067e+00,-4.326316203136791e+00,-7.350584553292913e+00,-1.005667710494159e+01,-1.136758324469110e+01,-2.435340144058522e+01,-2.834940842387552e+00,7.645006459053784e-01,-5.668978147327654e+00,-1.581069420754308e+01,-1.102587043153747e+01,-7.620632986868196e+00,-1.162241765255568e+01,-9.648450306112672e+00,2.939971011704519e+00,-5.006852317124548e+00,2.728166897736684e+00,-6.496671765515822e+00,-6.603984549792136e+01,-9.171478670274398e+00,-1.169777279849909e+02,-1.325686991339065e+01,-1.177325713972004e+01,-3.178931289780978e+01,-8.357812812484790e+00,2.758661312872158e+00,-8.623791950384232e+00,-4.487400302780387e-01,-6.539060722866687e+00,-7.180501284600570e+00,-1.550480140639377e+01,-1.184757583768368e+01,-1.079910659103120e+01,-9.033923959910632e+00,-5.895794778626384e+00,5.842845950425596e+00,5.245093960950418e-01,8.622071837055332e-01,-3.088039215216130e-01,-1.029646047239688e+01,-1.298620863255220e+00,-4.315723550216587e+00,-5.352920395858321e+00,-4.610247498630915e+00,-2.297565180652574e+00,-1.194284545025761e+00,-1.178036140607980e+00,3.766128440258103e+00,-5.716070050905542e+00,-5.567281555979353e+00,4.358130904877620e-01,5.903381990313943e-01,-6.712647192464055e+00,-5.628628838609790e+00,-3.520473062251919e+00,-6.969619686862290e+00,-6.210985621250042e+00,-3.972364775881728e+00,-1.274044385918228e+00,-2.230300594688791e+00,-4.190592595575932e-01,-1.237737503151706e+00,-5.206694583311733e-01,-6.797514200923261e-01,1.348189137676531e+00,4.548055178631917e+00,-4.577412389061903e+00,-7.983690065140640e-01,-1.510141701877411e+00,1.693970019490927e-01,-9.523438771775261e-01,1.220743950303155e+00,8.533704456551212e-01,1.673916589307460e+00,1.815334206076388e+00,-5.123263312916111e+00,-1.181106201885345e+01,-4.234339155433112e+00,-8.600136616869008e+00,-7.131861394498747e+00,-4.486424998881930e+00,-2.975011911059387e+00,-3.419887305224562e+00,-4.563184921525793e+00,-8.873622081742477e-01,-1.022479745194048e+00,3.393199277979143e+00,1.448178719002262e-01,-7.417157176714256e-01,-3.861681757795047e+00,-1.528945679440233e-01,-5.302597763461393e+00,2.378801632827010e+00,-1.701532712786066e+00,1.705767463168279e+00,-5.145271269182268e+00,-2.677565381818027e+00,2.423513286656655e+00,-1.985996483688428e+00,-4.976434046274590e+00,5.801677131244308e+00,-6.292225579817890e+00,2.600176716255446e+00,2.421955329186335e+00,-4.255918806821573e+00,2.872699464655817e+00,3.895014198119415e+00,-4.920223802310374e+00,-2.539146062167789e+00,8.824022590577802e-01,-5.821248955342347e+00,-2.350135418205281e+00,3.430780005056902e+00,4.345359801293291e-01,-5.030585290502282e+00,-4.906788685674732e+00,-2.039039808121438e+00,3.086006274871210e+00,-4.497125701108896e+00,1.886905573041937e-01,7.946242604715457e+00,3.569382971488285e+00,-1.109945483191129e+00,-3.010532168881033e+00,-3.396390856778245e+00,7.594240497018973e+00,2.379281597995030e-02,8.455005939908952e+00,1.052536532980351e+01,-1.098216894301932e+01,7.009795290702721e+00,-8.485789971470293e+00,-2.771962993245206e+00,-5.458737970867694e+00,1.507819438947296e+00,1.712176691775555e+00,3.229278625468862e-01,8.598350729734568e-01,2.041674625085228e-01,-1.917903111288663e+00,-6.967083332114391e-01,-1.144451251253517e+00,-5.720895469485523e-01,1.309991313940150e+00,-2.367443422756256e+00,-1.221993206089968e+00,1.183879164778671e+00,-6.389708014425870e-01,1.569149476803414e+00,-3.825906310641151e-01,4.960854909047673e+00,-4.984196304005491e+00,3.109229879968228e-01,4.680644289993386e-01,-1.145004084597327e+00,-7.052808043148528e-01,5.507536969007492e-01,-1.838162627335221e+00,-1.067476784241578e+00,-6.785890154563883e-01,7.014867564020556e-02,3.510960844082670e-03,1.569942540068749e+00,1.633538496757235e+00}; 
const float BIASVECTOR[]={-2.949952740246859e+00,-1.322749234238251e+00,1.722089877199271e+00,-6.588737711095294e-01,-3.025204841775470e-01,-1.305845427262503e+00,8.872506932249756e-01,-3.927170275592900e-02,-4.509465866296631e-01,-4.404879567594922e-02,-1.100435558293877e-01}; 
