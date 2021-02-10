// Copyright 2018 Yaki Studios, Inc. All Rights Reserved.

// FastNoise.cpp
//
// MIT License
//
// Copyright(c) 2017 Jordan Peck
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include "FastNoise.h"
#include "Curves/CurveFloat.h"

const FVector2D GRAD_2D[] =
{
	FVector2D(-1, -1), FVector2D(1, -1), FVector2D(-1, 1), FVector2D(1, 1),
	FVector2D(0, -1), FVector2D(-1, 0), FVector2D(0, 1), FVector2D(1, 0),
};

const FVector GRAD_3D[] =
{
	FVector(1, 1, 0), FVector(-1, 1, 0), FVector(1, -1, 0), FVector(-1, -1, 0),
	FVector(1, 0, 1), FVector(-1, 0, 1), FVector(1, 0, -1), FVector(-1, 0, -1),
	FVector(0, 1, 1), FVector(0, -1, 1), FVector(0, 1, -1), FVector(0, -1, -1),
	FVector(1, 1, 0), FVector(0, -1, 1), FVector(-1, 1, 0), FVector(0, -1, -1),
};

const FVector2D CELL_2D[] =
{
	FVector2D(-0.4313539279f, 0.1281943404f), FVector2D(-0.1733316799f, 0.415278375f),
	FVector2D(-0.2821957395f, -0.3505218461f), FVector2D(-0.2806473808f, 0.3517627718f),
	FVector2D(0.3125508975f, -0.3237467165f), FVector2D(0.3383018443f, -0.2967353402f),
	FVector2D(-0.4393982022f, -0.09710417025f), FVector2D(-0.4460443703f, -0.05953502905f),
	FVector2D(-0.302223039f, 0.3334085102f), FVector2D(-0.212681052f, -0.3965687458f),
	FVector2D(-0.2991156529f, 0.3361990872f), FVector2D(0.2293323691f, 0.3871778202f),
	FVector2D(0.4475439151f, -0.04695150755f), FVector2D(0.1777518f, 0.41340573f),
	FVector2D(0.1688522499f, -0.4171197882f), FVector2D(-0.0976597166f, 0.4392750616f),
	FVector2D(0.08450188373f, 0.4419948321f), FVector2D(-0.4098760448f, -0.1857461384f),
	FVector2D(0.3476585782f, -0.2857157906f), FVector2D(-0.3350670039f, -0.30038326f),
	FVector2D(0.2298190031f, -0.3868891648f), FVector2D(-0.01069924099f, 0.449872789f),
	FVector2D(-0.4460141246f, -0.05976119672f), FVector2D(0.3650293864f, 0.2631606867f),
	FVector2D(-0.349479423f, 0.2834856838f), FVector2D(-0.4122720642f, 0.1803655873f),
	FVector2D(-0.267327811f, 0.3619887311f), FVector2D(0.322124041f, -0.3142230135f),
	FVector2D(0.2880445931f, -0.3457315612f), FVector2D(0.3892170926f, -0.2258540565f),
	FVector2D(0.4492085018f, -0.02667811596f), FVector2D(-0.4497724772f, 0.01430799601f),
	FVector2D(0.1278175387f, -0.4314657307f), FVector2D(-0.03572100503f, 0.4485799926f),
	FVector2D(-0.4297407068f, -0.1335025276f), FVector2D(-0.3217817723f, 0.3145735065f),
	FVector2D(-0.3057158873f, 0.3302087162f), FVector2D(-0.414503978f, 0.1751754899f),
	FVector2D(-0.3738139881f, 0.2505256519f), FVector2D(0.2236891408f, -0.3904653228f),
	FVector2D(0.002967775577f, -0.4499902136f), FVector2D(0.1747128327f, -0.4146991995f),
	FVector2D(-0.4423772489f, -0.08247647938f), FVector2D(-0.2763960987f, -0.355112935f),
	FVector2D(-0.4019385906f, -0.2023496216f), FVector2D(0.3871414161f, -0.2293938184f),
	FVector2D(-0.430008727f, 0.1326367019f), FVector2D(-0.03037574274f, -0.4489736231f),
	FVector2D(-0.3486181573f, 0.2845441624f), FVector2D(0.04553517144f, -0.4476902368f),
	FVector2D(-0.0375802926f, 0.4484280562f), FVector2D(0.3266408905f, 0.3095250049f),
	FVector2D(0.06540017593f, -0.4452222108f), FVector2D(0.03409025829f, 0.448706869f),
	FVector2D(-0.4449193635f, 0.06742966669f), FVector2D(-0.4255936157f, -0.1461850686f),
	FVector2D(0.449917292f, 0.008627302568f), FVector2D(0.05242606404f, 0.4469356864f),
	FVector2D(-0.4495305179f, -0.02055026661f), FVector2D(-0.1204775703f, 0.4335725488f),
	FVector2D(-0.341986385f, -0.2924813028f), FVector2D(0.3865320182f, 0.2304191809f),
	FVector2D(0.04506097811f, -0.447738214f), FVector2D(-0.06283465979f, 0.4455915232f),
	FVector2D(0.3932600341f, -0.2187385324f), FVector2D(0.4472261803f, -0.04988730975f),
	FVector2D(0.3753571011f, -0.2482076684f), FVector2D(-0.273662295f, 0.357223947f),
	FVector2D(0.1700461538f, 0.4166344988f), FVector2D(0.4102692229f, 0.1848760794f),
	FVector2D(0.323227187f, -0.3130881435f), FVector2D(-0.2882310238f, -0.3455761521f),
	FVector2D(0.2050972664f, 0.4005435199f), FVector2D(0.4414085979f, -0.08751256895f),
	FVector2D(-0.1684700334f, 0.4172743077f), FVector2D(-0.003978032396f, 0.4499824166f),
	FVector2D(-0.2055133639f, 0.4003301853f), FVector2D(-0.006095674897f, -0.4499587123f),
	FVector2D(-0.1196228124f, -0.4338091548f), FVector2D(0.3901528491f, -0.2242337048f),
	FVector2D(0.01723531752f, 0.4496698165f), FVector2D(-0.3015070339f, 0.3340561458f),
	FVector2D(-0.01514262423f, -0.4497451511f), FVector2D(-0.4142574071f, -0.1757577897f),
	FVector2D(-0.1916377265f, -0.4071547394f), FVector2D(0.3749248747f, 0.2488600778f),
	FVector2D(-0.2237774255f, 0.3904147331f), FVector2D(-0.4166343106f, -0.1700466149f),
	FVector2D(0.3619171625f, 0.267424695f), FVector2D(0.1891126846f, -0.4083336779f),
	FVector2D(-0.3127425077f, 0.323561623f), FVector2D(-0.3281807787f, 0.307891826f),
	FVector2D(-0.2294806661f, 0.3870899429f), FVector2D(-0.3445266136f, 0.2894847362f),
	FVector2D(-0.4167095422f, -0.1698621719f), FVector2D(-0.257890321f, -0.3687717212f),
	FVector2D(-0.3612037825f, 0.2683874578f), FVector2D(0.2267996491f, 0.3886668486f),
	FVector2D(0.207157062f, 0.3994821043f), FVector2D(0.08355176718f, -0.4421754202f),
	FVector2D(-0.4312233307f, 0.1286329626f), FVector2D(0.3257055497f, 0.3105090899f),
	FVector2D(0.177701095f, -0.4134275279f), FVector2D(-0.445182522f, 0.06566979625f),
	FVector2D(0.3955143435f, 0.2146355146f), FVector2D(-0.4264613988f, 0.1436338239f),
	FVector2D(-0.3793799665f, -0.2420141339f), FVector2D(0.04617599081f, -0.4476245948f),
	FVector2D(-0.371405428f, -0.2540826796f), FVector2D(0.2563570295f, -0.3698392535f),
	FVector2D(0.03476646309f, 0.4486549822f), FVector2D(-0.3065454405f, 0.3294387544f),
	FVector2D(-0.2256979823f, 0.3893076172f), FVector2D(0.4116448463f, -0.1817925206f),
	FVector2D(-0.2907745828f, -0.3434387019f), FVector2D(0.2842278468f, -0.348876097f),
	FVector2D(0.3114589359f, -0.3247973695f), FVector2D(0.4464155859f, -0.0566844308f),
	FVector2D(-0.3037334033f, -0.3320331606f), FVector2D(0.4079607166f, 0.1899159123f),
	FVector2D(-0.3486948919f, -0.2844501228f), FVector2D(0.3264821436f, 0.3096924441f),
	FVector2D(0.3211142406f, 0.3152548881f), FVector2D(0.01183382662f, 0.4498443737f),
	FVector2D(0.4333844092f, 0.1211526057f), FVector2D(0.3118668416f, 0.324405723f),
	FVector2D(-0.272753471f, 0.3579183483f), FVector2D(-0.422228622f, -0.1556373694f),
	FVector2D(-0.1009700099f, -0.4385260051f), FVector2D(-0.2741171231f, -0.3568750521f),
	FVector2D(-0.1465125133f, 0.4254810025f), FVector2D(0.2302279044f, -0.3866459777f),
	FVector2D(-0.3699435608f, 0.2562064828f), FVector2D(0.105700352f, -0.4374099171f),
	FVector2D(-0.2646713633f, 0.3639355292f), FVector2D(0.3521828122f, 0.2801200935f),
	FVector2D(-0.1864187807f, -0.4095705534f), FVector2D(0.1994492955f, -0.4033856449f),
	FVector2D(0.3937065066f, 0.2179339044f), FVector2D(-0.3226158377f, 0.3137180602f),
	FVector2D(0.3796235338f, 0.2416318948f), FVector2D(0.1482921929f, 0.4248640083f),
	FVector2D(-0.407400394f, 0.1911149365f), FVector2D(0.4212853031f, 0.1581729856f),
	FVector2D(-0.2621297173f, 0.3657704353f), FVector2D(-0.2536986953f, -0.3716678248f),
	FVector2D(-0.2100236383f, 0.3979825013f), FVector2D(0.3624152444f, 0.2667493029f),
	FVector2D(-0.3645038479f, -0.2638881295f), FVector2D(0.2318486784f, 0.3856762766f),
	FVector2D(-0.3260457004f, 0.3101519002f), FVector2D(-0.2130045332f, -0.3963950918f),
	FVector2D(0.3814998766f, -0.2386584257f), FVector2D(-0.342977305f, 0.2913186713f),
	FVector2D(-0.4355865605f, 0.1129794154f), FVector2D(-0.2104679605f, 0.3977477059f),
	FVector2D(0.3348364681f, -0.3006402163f), FVector2D(0.3430468811f, 0.2912367377f),
	FVector2D(-0.2291836801f, -0.3872658529f), FVector2D(0.2547707298f, -0.3709337882f),
	FVector2D(0.4236174945f, -0.151816397f), FVector2D(-0.15387742f, 0.4228731957f),
	FVector2D(-0.4407449312f, 0.09079595574f), FVector2D(-0.06805276192f, -0.444824484f),
	FVector2D(0.4453517192f, -0.06451237284f), FVector2D(0.2562464609f, -0.3699158705f),
	FVector2D(0.3278198355f, -0.3082761026f), FVector2D(-0.4122774207f, -0.1803533432f),
	FVector2D(0.3354090914f, -0.3000012356f), FVector2D(0.446632869f, -0.05494615882f),
	FVector2D(-0.1608953296f, 0.4202531296f), FVector2D(-0.09463954939f, 0.4399356268f),
	FVector2D(-0.02637688324f, -0.4492262904f), FVector2D(0.447102804f, -0.05098119915f),
	FVector2D(-0.4365670908f, 0.1091291678f), FVector2D(-0.3959858651f, 0.2137643437f),
	FVector2D(-0.4240048207f, -0.1507312575f), FVector2D(-0.3882794568f, 0.2274622243f),
	FVector2D(-0.4283652566f, -0.1378521198f), FVector2D(0.3303888091f, 0.305521251f),
	FVector2D(0.3321434919f, -0.3036127481f), FVector2D(-0.413021046f, -0.1786438231f),
	FVector2D(0.08403060337f, -0.4420846725f), FVector2D(-0.3822882919f, 0.2373934748f),
	FVector2D(-0.3712395594f, -0.2543249683f), FVector2D(0.4472363971f, -0.04979563372f),
	FVector2D(-0.4466591209f, 0.05473234629f), FVector2D(0.0486272539f, -0.4473649407f),
	FVector2D(-0.4203101295f, -0.1607463688f), FVector2D(0.2205360833f, 0.39225481f),
	FVector2D(-0.3624900666f, 0.2666476169f), FVector2D(-0.4036086833f, -0.1989975647f),
	FVector2D(0.2152727807f, 0.3951678503f), FVector2D(-0.4359392962f, -0.1116106179f),
	FVector2D(0.4178354266f, 0.1670735057f), FVector2D(0.2007630161f, 0.4027334247f),
	FVector2D(-0.07278067175f, -0.4440754146f), FVector2D(0.3644748615f, -0.2639281632f),
	FVector2D(-0.4317451775f, 0.126870413f), FVector2D(-0.297436456f, 0.3376855855f),
	FVector2D(-0.2998672222f, 0.3355289094f), FVector2D(-0.2673674124f, 0.3619594822f),
	FVector2D(0.2808423357f, 0.3516071423f), FVector2D(0.3498946567f, 0.2829730186f),
	FVector2D(-0.2229685561f, 0.390877248f), FVector2D(0.3305823267f, 0.3053118493f),
	FVector2D(-0.2436681211f, -0.3783197679f), FVector2D(-0.03402776529f, 0.4487116125f),
	FVector2D(-0.319358823f, 0.3170330301f), FVector2D(0.4454633477f, -0.06373700535f),
	FVector2D(0.4483504221f, 0.03849544189f), FVector2D(-0.4427358436f, -0.08052932871f),
	FVector2D(0.05452298565f, 0.4466847255f), FVector2D(-0.2812560807f, 0.3512762688f),
	FVector2D(0.1266696921f, 0.4318041097f), FVector2D(-0.3735981243f, 0.2508474468f),
	FVector2D(0.2959708351f, -0.3389708908f), FVector2D(-0.3714377181f, 0.254035473f),
	FVector2D(-0.404467102f, -0.1972469604f), FVector2D(0.1636165687f, -0.419201167f),
	FVector2D(0.3289185495f, -0.3071035458f), FVector2D(-0.2494824991f, -0.3745109914f),
	FVector2D(0.03283133272f, 0.4488007393f), FVector2D(-0.166306057f, -0.4181414777f),
	FVector2D(-0.106833179f, 0.4371346153f), FVector2D(0.06440260376f, -0.4453676062f),
	FVector2D(-0.4483230967f, 0.03881238203f), FVector2D(-0.421377757f, -0.1579265206f),
	FVector2D(0.05097920662f, -0.4471030312f), FVector2D(0.2050584153f, -0.4005634111f),
	FVector2D(0.4178098529f, -0.167137449f), FVector2D(-0.3565189504f, -0.2745801121f),
	FVector2D(0.4478398129f, 0.04403977727f), FVector2D(-0.3399999602f, -0.2947881053f),
	FVector2D(0.3767121994f, 0.2461461331f), FVector2D(-0.3138934434f, 0.3224451987f),
	FVector2D(-0.1462001792f, -0.4255884251f), FVector2D(0.3970290489f, -0.2118205239f),
	FVector2D(0.4459149305f, -0.06049689889f), FVector2D(-0.4104889426f, -0.1843877112f),
	FVector2D(0.1475103971f, -0.4251360756f), FVector2D(0.09258030352f, 0.4403735771f),
	FVector2D(-0.1589664637f, -0.4209865359f), FVector2D(0.2482445008f, 0.3753327428f),
	FVector2D(0.4383624232f, -0.1016778537f), FVector2D(0.06242802956f, 0.4456486745f),
	FVector2D(0.2846591015f, -0.3485243118f), FVector2D(-0.344202744f, -0.2898697484f),
	FVector2D(0.1198188883f, -0.4337550392f), FVector2D(-0.243590703f, 0.3783696201f),
	FVector2D(0.2958191174f, -0.3391033025f), FVector2D(-0.1164007991f, 0.4346847754f),
	FVector2D(0.1274037151f, -0.4315881062f), FVector2D(0.368047306f, 0.2589231171f),
	FVector2D(0.2451436949f, 0.3773652989f), FVector2D(-0.4314509715f, 0.12786735f),
};

const FVector CELL_3D[] =
{
	FVector(0.1453787434f, -0.4149781685f, -0.0956981749f), FVector(-0.01242829687f, -0.1457918398f, -0.4255470325f),
	FVector(0.2877979582f, -0.02606483451f, -0.3449535616f), FVector(-0.07732986802f, 0.2377094325f, 0.3741848704f),
	FVector(0.1107205875f, -0.3552302079f, -0.2530858567f), FVector(0.2755209141f, 0.2640521179f, -0.238463215f),
	FVector(0.294168941f, 0.1526064594f, 0.3044271714f), FVector(0.4000921098f, -0.2034056362f, 0.03244149937f),
	FVector(-0.1697304074f, 0.3970864695f, -0.1265461359f), FVector(-0.1483224484f, -0.3859694688f, 0.1775613147f),
	FVector(0.2623596946f, -0.2354852944f, 0.2796677792f), FVector(-0.2709003183f, 0.3505271138f, -0.07901746678f),
	FVector(-0.03516550699f, 0.3885234328f, 0.2243054374f), FVector(-0.1267712655f, 0.1920044036f, 0.3867342179f),
	FVector(0.02952021915f, 0.4409685861f, 0.08470692262f), FVector(-0.2806854217f, -0.266996757f, 0.2289725438f),
	FVector(-0.171159547f, 0.2141185563f, 0.3568720405f), FVector(0.2113227183f, 0.3902405947f, -0.07453178509f),
	FVector(-0.1024352839f, 0.2128044156f, -0.3830421561f), FVector(-0.3304249877f, -0.1566986703f, 0.2622305365f),
	FVector(0.2091111325f, 0.3133278055f, -0.2461670583f), FVector(0.344678154f, -0.1944240454f, -0.2142341261f),
	FVector(0.1984478035f, -0.3214342325f, -0.2445373252f), FVector(-0.2929008603f, 0.2262915116f, 0.2559320961f),
	FVector(-0.1617332831f, 0.006314769776f, -0.4198838754f), FVector(-0.3582060271f, -0.148303178f, -0.2284613961f),
	FVector(-0.1852067326f, -0.3454119342f, -0.2211087107f), FVector(0.3046301062f, 0.1026310383f, 0.314908508f),
	FVector(-0.03816768434f, -0.2551766358f, -0.3686842991f), FVector(-0.4084952196f, 0.1805950793f, 0.05492788837f),
	FVector(-0.02687443361f, -0.2749741471f, 0.3551999201f), FVector(-0.03801098351f, 0.3277859044f, 0.3059600725f),
	FVector(0.2371120802f, 0.2900386767f, -0.2493099024f), FVector(0.4447660503f, 0.03946930643f, 0.05590469027f),
	FVector(0.01985147278f, -0.01503183293f, -0.4493105419f), FVector(0.4274339143f, 0.03345994256f, -0.1366772882f),
	FVector(-0.2072988631f, 0.2871414597f, -0.2776273824f), FVector(-0.3791240978f, 0.1281177671f, 0.2057929936f),
	FVector(-0.2098721267f, -0.1007087278f, -0.3851122467f), FVector(0.01582798878f, 0.4263894424f, 0.1429738373f),
	FVector(-0.1888129464f, -0.3160996813f, -0.2587096108f), FVector(0.1612988974f, -0.1974805082f, -0.3707885038f),
	FVector(-0.08974491322f, 0.229148752f, -0.3767448739f), FVector(0.07041229526f, 0.4150230285f, -0.1590534329f),
	FVector(-0.1082925611f, -0.1586061639f, 0.4069604477f), FVector(0.2474100658f, -0.3309414609f, 0.1782302128f),
	FVector(-0.1068836661f, -0.2701644537f, -0.3436379634f), FVector(0.2396452163f, 0.06803600538f, -0.3747549496f),
	FVector(-0.3063886072f, 0.2597428179f, 0.2028785103f), FVector(0.1593342891f, -0.3114350249f, -0.2830561951f),
	FVector(0.2709690528f, 0.1412648683f, -0.3303331794f), FVector(-0.1519780427f, 0.3623355133f, 0.2193527988f),
	FVector(0.1699773681f, 0.3456012883f, 0.2327390037f), FVector(-0.1986155616f, 0.3836276443f, -0.1260225743f),
	FVector(-0.1887482106f, -0.2050154888f, -0.353330953f), FVector(0.2659103394f, 0.3015631259f, -0.2021172246f),
	FVector(-0.08838976154f, -0.4288819642f, -0.1036702021f), FVector(-0.04201869311f, 0.3099592485f, 0.3235115047f),
	FVector(-0.3230334656f, 0.201549922f, -0.2398478873f), FVector(0.2612720941f, 0.2759854499f, -0.2409749453f),
	FVector(0.385713046f, 0.2193460345f, 0.07491837764f), FVector(0.07654967953f, 0.3721732183f, 0.241095919f),
	FVector(0.4317038818f, -0.02577753072f, 0.1243675091f), FVector(-0.2890436293f, -0.3418179959f, -0.04598084447f),
	FVector(-0.2201947582f, 0.383023377f, -0.08548310451f), FVector(0.4161322773f, -0.1669634289f, -0.03817251927f),
	FVector(0.2204718095f, 0.02654238946f, -0.391391981f), FVector(-0.1040307469f, 0.3890079625f, -0.2008741118f),
	FVector(-0.1432122615f, 0.371614387f, -0.2095065525f), FVector(0.3978380468f, -0.06206669342f, 0.2009293758f),
	FVector(-0.2599274663f, 0.2616724959f, -0.2578084893f), FVector(0.4032618332f, -0.1124593585f, 0.1650235939f),
	FVector(-0.08953470255f, -0.3048244735f, 0.3186935478f), FVector(0.118937202f, -0.2875221847f, 0.325092195f),
	FVector(0.02167047076f, -0.03284630549f, -0.4482761547f), FVector(-0.3411343612f, 0.2500031105f, 0.1537068389f),
	FVector(0.3162964612f, 0.3082064153f, -0.08640228117f), FVector(0.2355138889f, -0.3439334267f, -0.1695376245f),
	FVector(-0.02874541518f, -0.3955933019f, 0.2125550295f), FVector(-0.2461455173f, 0.02020282325f, -0.3761704803f),
	FVector(0.04208029445f, -0.4470439576f, 0.02968078139f), FVector(0.2727458746f, 0.2288471896f, -0.2752065618f),
	FVector(-0.1347522818f, -0.02720848277f, -0.4284874806f), FVector(0.3829624424f, 0.1231931484f, -0.2016512234f),
	FVector(-0.3547613644f, 0.1271702173f, 0.2459107769f), FVector(0.2305790207f, 0.3063895591f, 0.2354968222f),
	FVector(-0.08323845599f, -0.1922245118f, 0.3982726409f), FVector(0.2993663085f, -0.2619918095f, -0.2103333191f),
	FVector(-0.2154865723f, 0.2706747713f, 0.287751117f), FVector(0.01683355354f, -0.2680655787f, -0.3610505186f),
	FVector(0.05240429123f, 0.4335128183f, -0.1087217856f), FVector(0.00940104872f, -0.4472890582f, 0.04841609928f),
	FVector(0.3465688735f, 0.01141914583f, -0.2868093776f), FVector(-0.3706867948f, -0.2551104378f, 0.003156692623f),
	FVector(0.2741169781f, 0.2139972417f, -0.2855959784f), FVector(0.06413433865f, 0.1708718512f, 0.4113266307f),
	FVector(-0.388187972f, -0.03973280434f, -0.2241236325f), FVector(0.06419469312f, -0.2803682491f, 0.3460819069f),
	FVector(-0.1986120739f, -0.3391173584f, 0.2192091725f), FVector(-0.203203009f, -0.3871641506f, 0.1063600375f),
	FVector(-0.1389736354f, -0.2775901578f, -0.3257760473f), FVector(-0.06555641638f, 0.342253257f, -0.2847192729f),
	FVector(-0.2529246486f, -0.2904227915f, 0.2327739768f), FVector(0.1444476522f, 0.1069184044f, 0.4125570634f),
	FVector(-0.3643780054f, -0.2447099973f, -0.09922543227f), FVector(0.4286142488f, -0.1358496089f, -0.01829506817f),
	FVector(0.165872923f, -0.3136808464f, -0.2767498872f), FVector(0.2219610524f, -0.3658139958f, 0.1393320198f),
	FVector(0.04322940318f, -0.3832730794f, 0.2318037215f), FVector(-0.08481269795f, -0.4404869674f, -0.03574965489f),
	FVector(0.1822082075f, -0.3953259299f, 0.1140946023f), FVector(-0.3269323334f, 0.3036542563f, 0.05838957105f),
	FVector(-0.4080485344f, 0.04227858267f, -0.184956522f), FVector(0.2676025294f, -0.01299671652f, 0.36155217f),
	FVector(0.3024892441f, -0.1009990293f, -0.3174892964f), FVector(0.1448494052f, 0.425921681f, -0.0104580805f),
	FVector(0.4198402157f, 0.08062320474f, 0.1404780841f), FVector(-0.3008872161f, -0.333040905f, -0.03241355801f),
	FVector(0.3639310428f, -0.1291284382f, -0.2310412139f), FVector(0.3295806598f, 0.0184175994f, -0.3058388149f),
	FVector(0.2776259487f, -0.2974929052f, -0.1921504723f), FVector(0.4149000507f, -0.144793182f, -0.09691688386f),
	FVector(0.145016715f, -0.0398992945f, 0.4241205002f), FVector(0.09299023471f, -0.299732164f, -0.3225111565f),
	FVector(0.1028907093f, -0.361266869f, 0.247789732f), FVector(0.2683057049f, -0.07076041213f, -0.3542668666f),
	FVector(-0.4227307273f, -0.07933161816f, -0.1323073187f), FVector(-0.1781224702f, 0.1806857196f, -0.3716517945f),
	FVector(0.4390788626f, -0.02841848598f, -0.09435116353f), FVector(0.2972583585f, 0.2382799621f, -0.2394997452f),
	FVector(-0.1707002821f, 0.2215845691f, 0.3525077196f), FVector(0.3806686614f, 0.1471852559f, -0.1895464869f),
	FVector(-0.1751445661f, -0.274887877f, 0.3102596268f), FVector(-0.2227237566f, -0.2316778837f, 0.3149912482f),
	FVector(0.1369633021f, 0.1341343041f, -0.4071228836f), FVector(-0.3529503428f, -0.2472893463f, -0.129514612f),
	FVector(-0.2590744185f, -0.2985577559f, -0.2150435121f), FVector(-0.3784019401f, 0.2199816631f, -0.1044989934f),
	FVector(-0.05635805671f, 0.1485737441f, 0.4210102279f), FVector(0.3251428613f, 0.09666046873f, -0.2957006485f),
	FVector(-0.4190995804f, 0.1406751354f, -0.08405978803f), FVector(-0.3253150961f, -0.3080335042f, -0.04225456877f),
	FVector(0.2857945863f, -0.05796152095f, 0.3427271751f), FVector(-0.2733604046f, 0.1973770973f, -0.2980207554f),
	FVector(0.219003657f, 0.2410037886f, -0.3105713639f), FVector(0.3182767252f, -0.271342949f, 0.1660509868f),
	FVector(-0.03222023115f, -0.3331161506f, -0.300824678f), FVector(-0.3087780231f, 0.1992794134f, -0.2596995338f),
	FVector(-0.06487611647f, -0.4311322747f, 0.1114273361f), FVector(0.3921171432f, -0.06294284106f, -0.2116183942f),
	FVector(-0.1606404506f, -0.358928121f, -0.2187812825f), FVector(-0.03767771199f, -0.2290351443f, 0.3855169162f),
	FVector(0.1394866832f, -0.3602213994f, 0.2308332918f), FVector(-0.4345093872f, 0.005751117145f, 0.1169124335f),
	FVector(-0.1044637494f, 0.4168128432f, -0.1336202785f), FVector(0.2658727501f, 0.2551943237f, 0.2582393035f),
	FVector(0.2051461999f, 0.1975390727f, 0.3484154868f), FVector(-0.266085566f, 0.23483312f, 0.2766800993f),
	FVector(0.07849405464f, -0.3300346342f, -0.2956616708f), FVector(-0.2160686338f, 0.05376451292f, -0.3910546287f),
	FVector(-0.185779186f, 0.2148499206f, 0.3490352499f), FVector(0.02492421743f, -0.3229954284f, -0.3123343347f),
	FVector(-0.120167831f, 0.4017266681f, 0.1633259825f), FVector(-0.02160084693f, -0.06885389554f, 0.4441762538f),
	FVector(0.2597670064f, 0.3096300784f, 0.1978643903f), FVector(-0.1611553854f, -0.09823036005f, 0.4085091653f),
	FVector(-0.3278896792f, 0.1461670309f, 0.2713366126f), FVector(0.2822734956f, 0.03754421121f, -0.3484423997f),
	FVector(0.03169341113f, 0.347405252f, -0.2842624114f), FVector(0.2202613604f, -0.3460788041f, -0.1849713341f),
	FVector(0.2933396046f, 0.3031973659f, 0.1565989581f), FVector(-0.3194922995f, 0.2453752201f, -0.200538455f),
	FVector(-0.3441586045f, -0.1698856132f, -0.2349334659f), FVector(0.2703645948f, -0.3574277231f, 0.04060059933f),
	FVector(0.2298568861f, 0.3744156221f, 0.0973588921f), FVector(0.09326603877f, -0.3170108894f, 0.3054595587f),
	FVector(-0.1116165319f, -0.2985018719f, 0.3177080142f), FVector(0.2172907365f, -0.3460005203f, -0.1885958001f),
	FVector(0.1991339479f, 0.3820341668f, -0.1299829458f), FVector(-0.0541918155f, -0.2103145071f, 0.39412061f),
	FVector(0.08871336998f, 0.2012117383f, 0.3926114802f), FVector(0.2787673278f, 0.3505404674f, 0.04370535101f),
	FVector(-0.322166438f, 0.3067213525f, 0.06804996813f), FVector(-0.4277366384f, 0.132066775f, 0.04582286686f),
	FVector(0.240131882f, -0.1612516055f, 0.344723946f), FVector(0.1448607981f, -0.2387819045f, 0.3528435224f),
	FVector(-0.3837065682f, -0.2206398454f, 0.08116235683f), FVector(-0.4382627882f, -0.09082753406f, -0.04664855374f),
	FVector(-0.37728353f, 0.05445141085f, 0.2391488697f), FVector(0.1259579313f, 0.348394558f, 0.2554522098f),
	FVector(-0.1406285511f, -0.270877371f, -0.3306796947f), FVector(-0.1580694418f, 0.4162931958f, -0.06491553533f),
	FVector(0.2477612106f, -0.2927867412f, -0.2353514536f), FVector(0.2916132853f, 0.3312535401f, 0.08793624968f),
	FVector(0.07365265219f, -0.1666159848f, 0.411478311f), FVector(-0.26126526f, -0.2422237692f, 0.2748965434f),
	FVector(-0.3721862032f, 0.252790166f, 0.008634938242f), FVector(-0.3691191571f, -0.255281188f, 0.03290232422f),
	FVector(0.2278441737f, -0.3358364886f, 0.1944244981f), FVector(0.363398169f, -0.2310190248f, 0.1306597909f),
	FVector(-0.304231482f, -0.2698452035f, 0.1926830856f), FVector(-0.3199312232f, 0.316332536f, -0.008816977938f),
	FVector(0.2874852279f, 0.1642275508f, -0.304764754f), FVector(-0.1451096801f, 0.3277541114f, -0.2720669462f),
	FVector(0.3220090754f, 0.0511344108f, 0.3101538769f), FVector(-0.1247400865f, -0.04333605335f, -0.4301882115f),
	FVector(-0.2829555867f, -0.3056190617f, -0.1703910946f), FVector(0.1069384374f, 0.3491024667f, -0.2630430352f),
	FVector(-0.1420661144f, -0.3055376754f, -0.2982682484f), FVector(-0.250548338f, 0.3156466809f, -0.2002316239f),
	FVector(0.3265787872f, 0.1871229129f, 0.2466400438f), FVector(0.07646097258f, -0.3026690852f, 0.324106687f),
	FVector(0.3451771584f, 0.2757120714f, -0.0856480183f), FVector(0.298137964f, 0.2852657134f, 0.179547284f),
	FVector(0.2812250376f, 0.3466716415f, 0.05684409612f), FVector(0.4390345476f, -0.09790429955f, -0.01278335452f),
	FVector(0.2148373234f, 0.1850172527f, 0.3494474791f), FVector(0.2595421179f, -0.07946825393f, 0.3589187731f),
	FVector(0.3182823114f, -0.307355516f, -0.08203022006f), FVector(-0.4089859285f, -0.04647718411f, 0.1818526372f),
	FVector(-0.2826749061f, 0.07417482322f, 0.3421885344f), FVector(0.3483864637f, 0.225442246f, -0.1740766085f),
	FVector(-0.3226415069f, -0.1420585388f, -0.2796816575f), FVector(0.4330734858f, -0.118868561f, -0.02859407492f),
	FVector(-0.08717822568f, -0.3909896417f, -0.2050050172f), FVector(-0.2149678299f, 0.3939973956f, -0.03247898316f),
	FVector(-0.2687330705f, 0.322686276f, -0.1617284888f), FVector(0.2105665099f, -0.1961317136f, -0.3459683451f),
	FVector(0.4361845915f, -0.1105517485f, 0.004616608544f), FVector(0.05333333359f, -0.313639498f, -0.3182543336f),
	FVector(-0.05986216652f, 0.1361029153f, -0.4247264031f), FVector(0.3664988455f, 0.2550543014f, -0.05590974511f),
	FVector(-0.2341015558f, -0.182405731f, 0.3382670703f), FVector(-0.04730947785f, -0.4222150243f, -0.1483114513f),
	FVector(-0.2391566239f, -0.2577696514f, -0.2808182972f), FVector(-0.1242081035f, 0.4256953395f, -0.07652336246f),
	FVector(0.2614832715f, -0.3650179274f, 0.02980623099f), FVector(-0.2728794681f, -0.3499628774f, 0.07458404908f),
	FVector(0.007892900508f, -0.1672771315f, 0.4176793787f), FVector(-0.01730330376f, 0.2978486637f, -0.3368779738f),
	FVector(0.2054835762f, -0.3252600376f, -0.2334146693f), FVector(-0.3231994983f, 0.1564282844f, -0.2712420987f),
	FVector(-0.2669545963f, 0.2599343665f, -0.2523278991f), FVector(-0.05554372779f, 0.3170813944f, -0.3144428146f),
	FVector(-0.2083935713f, -0.310922837f, -0.2497981362f), FVector(0.06989323478f, -0.3156141536f, 0.3130537363f),
	FVector(0.3847566193f, -0.1605309138f, -0.1693876312f), FVector(-0.3026215288f, -0.3001537679f, -0.1443188342f),
	FVector(0.3450735512f, 0.08611519592f, 0.2756962409f), FVector(0.1814473292f, -0.2788782453f, -0.3029914042f),
	FVector(-0.03855010448f, 0.09795110726f, 0.4375151083f), FVector(0.3533670318f, 0.2665752752f, 0.08105160988f),
	FVector(-0.007945601311f, 0.140359426f, -0.4274764309f), FVector(0.4063099273f, -0.1491768253f, -0.1231199324f),
	FVector(-0.2016773589f, 0.008816271194f, -0.4021797064f), FVector(-0.07527055435f, -0.425643481f, -0.1251477955f),
};


const uint8 SIMPLEX_4D[] =
{
	0, 1, 2, 3, 0, 1, 3, 2, 0, 0, 0, 0, 0, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0,
	0, 2, 1, 3, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 2, 0, 3, 0, 0, 0, 0, 1, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 1, 2, 3, 1, 0,
	1, 0, 2, 3, 1, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 1, 0, 0, 0, 0, 2, 1, 3, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	2, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 3, 0, 2, 1, 0, 0, 0, 0, 3, 1, 2, 0,
	2, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 2, 0, 0, 0, 0, 3, 2, 0, 1, 3, 2, 1, 0
};

float InterpHermiteFunc(float t) { return t * t * (3 - 2 * t); }
float InterpQuinticFunc(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

float CubicLerp(float a, float b, float c, float d, float t)
{
	float p = (d - c) - (a - b);
	return t * t * t * p + t * t * ((a - b) - p) + t * (c - a) + b;
}


// Hashing
const int32 X_PRIME = 1619;
const int32 Y_PRIME = 31337;
const int32 Z_PRIME = 6971;
const int32 W_PRIME = 1013;

const float F2 = static_cast<float>(1.0 / 2.0);
const float G2 = static_cast<float>(1.0 / 4.0);

const float F3 = static_cast<float>(1.0 / 3.0);
const float G3 = static_cast<float>(1.0 / 6.0);
const float G33 = G3 * 3 - 1;

const float F4 = static_cast<float>((2.23606797 - 1.0) / 4.0);
const float G4 = static_cast<float>((5.0 - 2.23606797) / 20.0);

const float CUBIC_3D_BOUNDING = 1 / (static_cast<float>(1.5) * static_cast<float>(1.5) * static_cast<float>(1.5));
const float CUBIC_2D_BOUNDING = 1 / (static_cast<float>(1.5) * static_cast<float>(1.5));


int32 UNoiseBlueprintFunctionLibrary::Hash2D(int32 Seed, const int32& x, const int32& y)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	return Seed;
}

int32 UNoiseBlueprintFunctionLibrary::Hash3D(int32 Seed, const int32& x, const int32& y, const int32& z)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;
	Seed ^= Z_PRIME * z;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	return Seed;
}

int32 UNoiseBlueprintFunctionLibrary::Hash4D(int32 Seed, const int32& x, const int32& y, const int32& z, const int32& w)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;
	Seed ^= Z_PRIME * z;
	Seed ^= W_PRIME * w;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	return Seed;
}

float UNoiseBlueprintFunctionLibrary::ValCoord2D(int32 Seed, const int32& x, const int32& y)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;

	return (Seed * Seed * Seed * 60493) / static_cast<float>(2147483648);
}

float UNoiseBlueprintFunctionLibrary::ValCoord3D(int32 Seed, const int32& x, const int32& y, const int32& z)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;
	Seed ^= Z_PRIME * z;

	return (Seed * Seed * Seed * 60493) / static_cast<float>(2147483648);
}

float UNoiseBlueprintFunctionLibrary::ValCoord4D(int32 Seed, const int32& x, const int32& y, const int32& z,
                                                 const int32& w)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;
	Seed ^= Z_PRIME * z;
	Seed ^= W_PRIME * w;

	return (Seed * Seed * Seed * 60493) / static_cast<float>(2147483648);
}

float UNoiseBlueprintFunctionLibrary::GradCoord2D(int32 Seed, const int32& x, const int32& y, const float& xd,
                                                  const float& yd)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	const FVector2D g = GRAD_2D[Seed & 7];

	return xd * g.X + yd * g.Y;
}

float UNoiseBlueprintFunctionLibrary::GradCoord3D(int32 Seed, const int32& x, const int32& y, const int32& z,
                                                  const float& xd, const float& yd, const float& zd)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;
	Seed ^= Z_PRIME * z;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	const FVector g = GRAD_3D[Seed & 15];

	return xd * g.X + yd * g.Y + zd * g.Z;
}

float UNoiseBlueprintFunctionLibrary::GradCoord4D(int32 Seed, const int32& x, const int32& y, const int32& z,
                                                  const int32& w, const float& xd, const float& yd, const float& zd,
                                                  const float& wd)
{
	Seed ^= X_PRIME * x;
	Seed ^= Y_PRIME * y;
	Seed ^= Z_PRIME * z;
	Seed ^= W_PRIME * w;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	Seed &= 31;
	float a = yd, b = zd, c = wd; // X,Y,Z
	switch (Seed >> 3)
	{
		// OR, DEPENDING ON HIGH ORDER 2 BITS:
	case 1:
		a = wd;
		b = xd;
		c = yd;
		break; // W,X,Y
	case 2:
		a = zd;
		b = wd;
		c = xd;
		break; // Z,W,X
	case 3:
		a = yd;
		b = zd;
		c = wd;
		break; // Y,Z,W
	}
	return ((Seed & 4) == 0 ? -a : a) + ((Seed & 2) == 0 ? -b : b) + ((Seed & 1) == 0 ? -c : c);
}

// White Noise
float UNoiseBlueprintFunctionLibrary::GetWhiteNoise(const int32& Seed, float x, float y, float z, float w)
{
	return ValCoord4D(Seed,
	                  *reinterpret_cast<int32*>(&x) ^ (*reinterpret_cast<int32*>(&x) >> 16),
	                  *reinterpret_cast<int32*>(&y) ^ (*reinterpret_cast<int32*>(&y) >> 16),
	                  *reinterpret_cast<int32*>(&z) ^ (*reinterpret_cast<int32*>(&z) >> 16),
	                  *reinterpret_cast<int32*>(&w) ^ (*reinterpret_cast<int32*>(&w) >> 16));
}

float UNoiseBlueprintFunctionLibrary::GetWhiteNoise(const int32& Seed, float x, float y, float z)
{
	return ValCoord3D(Seed,
	                  *reinterpret_cast<int32*>(&x) ^ (*reinterpret_cast<int32*>(&x) >> 16),
	                  *reinterpret_cast<int32*>(&y) ^ (*reinterpret_cast<int32*>(&y) >> 16),
	                  *reinterpret_cast<int32*>(&z) ^ (*reinterpret_cast<int32*>(&z) >> 16));
}

float UNoiseBlueprintFunctionLibrary::GetWhiteNoise(const int32& Seed, float x, float y)
{
	return ValCoord2D(Seed,
	                  *reinterpret_cast<int32*>(&x) ^ (*reinterpret_cast<int32*>(&x) >> 16),
	                  *reinterpret_cast<int32*>(&y) ^ (*reinterpret_cast<int32*>(&y) >> 16));
}

// Value Noise
float UNoiseBlueprintFunctionLibrary::GetValueFractal(const int32& Seed, const float& Frequency,
                                                      const float& Lacunarity, const float& Gain, const int32& Octaves,
                                                      const EInterp& Interpolation, const EFractalType& FractalType,
                                                      const FVector& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleValueFractalFBM(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::Billow:
		return SingleValueFractalBillow(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SingleValueFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SingleValueFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                            const int32& Octaves, const EInterp& Interpolation,
                                                            FVector Coordinates)
{
	float sum = SingleValue(Seed, Interpolation, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;


	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SingleValue(++Seed, Interpolation, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}
	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleValueFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                               const int32& Octaves, const EInterp& Interpolation,
                                                               FVector Coordinates)
{
	float sum = FMath::Abs(SingleValue(Seed, Interpolation, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SingleValue(++Seed, Interpolation, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}
	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleValueFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                    const float& Gain, const int32& Octaves,
                                                                    const EInterp& Interpolation, FVector Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}

	float sig = 1 - FMath::Abs(SingleValue(Seed, Interpolation, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;
	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SingleValue(++Seed, Interpolation, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::GetValue(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
                                               const FVector& Coordinates)
{
	return SingleValue(Seed, Interpolation, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SingleValue(const int32& Seed, const EInterp& Interpolation,
                                                  const FVector& Coordinates)
{
	const int32 x0 = FMath::FloorToInt(Coordinates.X);
	const int32 y0 = FMath::FloorToInt(Coordinates.Y);
	const int32 z0 = FMath::FloorToInt(Coordinates.Z);
	const int32 x1 = x0 + 1;
	const int32 y1 = y0 + 1;
	const int32 z1 = z0 + 1;

	float xs = 0, ys = 0, zs = 0;
	switch (Interpolation)
	{
	case EInterp::Linear:
		xs = Coordinates.X - static_cast<float>(x0);
		ys = Coordinates.Y - static_cast<float>(y0);
		zs = Coordinates.Z - static_cast<float>(z0);
		break;
	case EInterp::Hermite:
		xs = InterpHermiteFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpHermiteFunc(Coordinates.Y - static_cast<float>(y0));
		zs = InterpHermiteFunc(Coordinates.Z - static_cast<float>(z0));
		break;
	case EInterp::Quintic:
		xs = InterpQuinticFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpQuinticFunc(Coordinates.Y - static_cast<float>(y0));
		zs = InterpQuinticFunc(Coordinates.Z - static_cast<float>(z0));
		break;
	}

	const float xf00 = FMath::Lerp(ValCoord3D(Seed, x0, y0, z0), ValCoord3D(Seed, x1, y0, z0), xs);
	const float xf10 = FMath::Lerp(ValCoord3D(Seed, x0, y1, z0), ValCoord3D(Seed, x1, y1, z0), xs);
	const float xf01 = FMath::Lerp(ValCoord3D(Seed, x0, y0, z1), ValCoord3D(Seed, x1, y0, z1), xs);
	const float xf11 = FMath::Lerp(ValCoord3D(Seed, x0, y1, z1), ValCoord3D(Seed, x1, y1, z1), xs);

	const float yf0 = FMath::Lerp(xf00, xf10, ys);
	const float yf1 = FMath::Lerp(xf01, xf11, ys);

	return FMath::Lerp(yf0, yf1, zs);
}

float UNoiseBlueprintFunctionLibrary::GetValueFractal(const int32& Seed, const float& Frequency,
                                                      const float& Lacunarity, const float& Gain, const int32& Octaves,
                                                      const EInterp& Interpolation, const EFractalType& FractalType,
                                                      const FVector2D& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleValueFractalFBM(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::Billow:
		return SingleValueFractalBillow(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SingleValueFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SingleValueFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                            const int32& Octaves, const EInterp& Interpolation,
                                                            FVector2D Coordinates)
{
	float sum = SingleValue(Seed, Interpolation, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SingleValue(++Seed, Interpolation, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}
	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleValueFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                               const int32& Octaves, const EInterp& Interpolation,
                                                               FVector2D Coordinates)
{
	float sum = FMath::Abs(SingleValue(Seed, Interpolation, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SingleValue(++Seed, Interpolation, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleValueFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                    const float& Gain, const int32& Octaves,
                                                                    const EInterp& Interpolation, FVector2D Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}


	float sig = 1 - FMath::Abs(SingleValue(Seed, Interpolation, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;
	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SingleValue(++Seed, Interpolation, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::GetValue(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
                                               const FVector2D& Coordinates)
{
	return SingleValue(Seed, Interpolation, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SingleValue(const int32& Seed, const EInterp& Interpolation,
                                                  const FVector2D& Coordinates)
{
	const int32 x0 = FMath::FloorToInt(Coordinates.X);
	const int32 y0 = FMath::FloorToInt(Coordinates.Y);
	const int32 x1 = x0 + 1;
	const int32 y1 = y0 + 1;

	float xs = 0, ys = 0;
	switch (Interpolation)
	{
	case EInterp::Linear:
		xs = Coordinates.X - static_cast<float>(x0);
		ys = Coordinates.Y - static_cast<float>(y0);
		break;
	case EInterp::Hermite:
		xs = InterpHermiteFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpHermiteFunc(Coordinates.Y - static_cast<float>(y0));
		break;
	case EInterp::Quintic:
		xs = InterpQuinticFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpQuinticFunc(Coordinates.Y - static_cast<float>(y0));
		break;
	}

	const float xf0 = FMath::Lerp(ValCoord2D(Seed, x0, y0), ValCoord2D(Seed, x1, y0), xs);
	const float xf1 = FMath::Lerp(ValCoord2D(Seed, x0, y1), ValCoord2D(Seed, x1, y1), xs);

	return FMath::Lerp(xf0, xf1, ys);
}

// Perlin Noise
float UNoiseBlueprintFunctionLibrary::GetPerlinFractal(const int32& Seed, const float& Frequency,
                                                       const float& Lacunarity, const float& Gain, const int32& Octaves,
                                                       const EInterp& Interpolation, const EFractalType& FractalType,
                                                       const FVector& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SinglePerlinFractalFBM(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::Billow:
		return SinglePerlinFractalBillow(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SinglePerlinFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SinglePerlinFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                             const int32& Octaves, const EInterp& Interpolation,
                                                             FVector Coordinates)
{
	float sum = SinglePerlin(Seed, Interpolation, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SinglePerlin(++Seed, Interpolation, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SinglePerlinFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                                const int32& Octaves, const EInterp& Interpolation,
                                                                FVector Coordinates)
{
	float sum = FMath::Abs(SinglePerlin(Seed, Interpolation, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SinglePerlin(++Seed, Interpolation, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SinglePerlinFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                     const float& Gain, const int32& Octaves,
                                                                     const EInterp& Interpolation, FVector Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}

	float sig = 1 - FMath::Abs(SinglePerlin(Seed, Interpolation, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;
	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SinglePerlin(++Seed, Interpolation, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::GetPerlin(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
                                                const FVector& Coordinates)
{
	return SinglePerlin(Seed, Interpolation, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SinglePerlin(const int32& Seed, const EInterp& Interpolation,
                                                   const FVector& Coordinates)
{
	const int32 x0 = FMath::FloorToInt(Coordinates.X);
	const int32 y0 = FMath::FloorToInt(Coordinates.Y);
	const int32 z0 = FMath::FloorToInt(Coordinates.Z);
	const int32 x1 = x0 + 1;
	const int32 y1 = y0 + 1;
	const int32 z1 = z0 + 1;

	float xs = 0, ys = 0, zs = 0;
	switch (Interpolation)
	{
	case EInterp::Linear:
		xs = Coordinates.X - static_cast<float>(x0);
		ys = Coordinates.Y - static_cast<float>(y0);
		zs = Coordinates.Z - static_cast<float>(z0);
		break;
	case EInterp::Hermite:
		xs = InterpHermiteFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpHermiteFunc(Coordinates.Y - static_cast<float>(y0));
		zs = InterpHermiteFunc(Coordinates.Z - static_cast<float>(z0));
		break;
	case EInterp::Quintic:
		xs = InterpQuinticFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpQuinticFunc(Coordinates.Y - static_cast<float>(y0));
		zs = InterpQuinticFunc(Coordinates.Z - static_cast<float>(z0));
		break;
	}

	const float xd0 = Coordinates.X - static_cast<float>(x0);
	const float yd0 = Coordinates.Y - static_cast<float>(y0);
	const float zd0 = Coordinates.Z - static_cast<float>(z0);
	const float xd1 = xd0 - 1;
	const float yd1 = yd0 - 1;
	const float zd1 = zd0 - 1;

	const float xf00 = FMath::Lerp(GradCoord3D(Seed, x0, y0, z0, xd0, yd0, zd0),
	                               GradCoord3D(Seed, x1, y0, z0, xd1, yd0, zd0), xs);
	const float xf10 = FMath::Lerp(GradCoord3D(Seed, x0, y1, z0, xd0, yd1, zd0),
	                               GradCoord3D(Seed, x1, y1, z0, xd1, yd1, zd0), xs);
	const float xf01 = FMath::Lerp(GradCoord3D(Seed, x0, y0, z1, xd0, yd0, zd1),
	                               GradCoord3D(Seed, x1, y0, z1, xd1, yd0, zd1), xs);
	const float xf11 = FMath::Lerp(GradCoord3D(Seed, x0, y1, z1, xd0, yd1, zd1),
	                               GradCoord3D(Seed, x1, y1, z1, xd1, yd1, zd1), xs);

	const float yf0 = FMath::Lerp(xf00, xf10, ys);
	const float yf1 = FMath::Lerp(xf01, xf11, ys);

	return FMath::Lerp(yf0, yf1, zs);
}

float UNoiseBlueprintFunctionLibrary::GetPerlinFractal(const int32& Seed, const float& Frequency,
                                                       const float& Lacunarity, const float& Gain, const int32& Octaves,
                                                       const EInterp& Interpolation, const EFractalType& FractalType,
                                                       const FVector2D& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SinglePerlinFractalFBM(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::Billow:
		return SinglePerlinFractalBillow(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SinglePerlinFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Interpolation, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SinglePerlinFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                             const int32& Octaves, const EInterp& Interpolation,
                                                             FVector2D Coordinates)
{
	float sum = SinglePerlin(Seed, Interpolation, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SinglePerlin(++Seed, Interpolation, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SinglePerlinFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                                const int32& Octaves, const EInterp& Interpolation,
                                                                FVector2D Coordinates)
{
	float sum = FMath::Abs(SinglePerlin(Seed, Interpolation, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SinglePerlin(++Seed, Interpolation, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SinglePerlinFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                     const float& Gain, const int32& Octaves,
                                                                     const EInterp& Interpolation,
                                                                     FVector2D Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}

	float sig = 1 - FMath::Abs(SinglePerlin(Seed, Interpolation, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;
	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SinglePerlin(++Seed, Interpolation, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::GetPerlin(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
                                                const FVector2D& Coordinates)
{
	return SinglePerlin(Seed, Interpolation, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SinglePerlin(const int32& Seed, const EInterp& Interpolation,
                                                   const FVector2D& Coordinates)
{
	const int32 x0 = FMath::FloorToInt(Coordinates.X);
	const int32 y0 = FMath::FloorToInt(Coordinates.Y);
	const int32 x1 = x0 + 1;
	const int32 y1 = y0 + 1;

	float xs = 0, ys = 0;
	switch (Interpolation)
	{
	case EInterp::Linear:
		xs = Coordinates.X - static_cast<float>(x0);
		ys = Coordinates.Y - static_cast<float>(y0);
		break;
	case EInterp::Hermite:
		xs = InterpHermiteFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpHermiteFunc(Coordinates.Y - static_cast<float>(y0));
		break;
	case EInterp::Quintic:
		xs = InterpQuinticFunc(Coordinates.X - static_cast<float>(x0));
		ys = InterpQuinticFunc(Coordinates.Y - static_cast<float>(y0));
		break;
	}
	const float xd0 = Coordinates.X - static_cast<float>(x0);
	const float yd0 = Coordinates.Y - static_cast<float>(y0);
	const float xd1 = xd0 - 1;
	const float yd1 = yd0 - 1;

	const float xf0 = FMath::Lerp(GradCoord2D(Seed, x0, y0, xd0, yd0), GradCoord2D(Seed, x1, y0, xd1, yd0), xs);
	const float xf1 = FMath::Lerp(GradCoord2D(Seed, x0, y1, xd0, yd1), GradCoord2D(Seed, x1, y1, xd1, yd1), xs);

	return FMath::Lerp(xf0, xf1, ys);
}

// Simplex Noise

float UNoiseBlueprintFunctionLibrary::GetSimplexFractal(const int32& Seed, const float& Frequency,
                                                        const float& Lacunarity, const float& Gain,
                                                        const int32& Octaves, const EFractalType& FractalType,
                                                        const FVector& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleSimplexFractalFBM(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::Billow:
		return SingleSimplexFractalBillow(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SingleSimplexFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SingleSimplexFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                              const int32& Octaves, FVector Coordinates)
{
	float sum = SingleSimplex(Seed, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SingleSimplex(++Seed, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleSimplexFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                                 const int32& Octaves, FVector Coordinates)
{
	float sum = FMath::Abs(SingleSimplex(Seed, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SingleSimplex(++Seed, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleSimplexFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                      const float& Gain, const int32& Octaves,
                                                                      FVector Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}

	float sig = 1 - FMath::Abs(SingleSimplex(Seed, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;
	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SingleSimplex(++Seed, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::GetSimplex(const int32& Seed, const float& Frequency, const FVector& Coordinates)
{
	return SingleSimplex(Seed, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SingleSimplex(const int32& Seed, const FVector& Coordinates)
{
	float t = (Coordinates.X + Coordinates.Y + Coordinates.Z) * F3;
	const int32 i = FMath::FloorToInt(Coordinates.X + t);
	const int32 j = FMath::FloorToInt(Coordinates.Y + t);
	const int32 k = FMath::FloorToInt(Coordinates.Z + t);

	t = (i + j + k) * G3;
	const float x0 = Coordinates.X - (i - t);
	const float y0 = Coordinates.Y - (j - t);
	const float z0 = Coordinates.Z - (k - t);

	int32 i1, j1, k1;
	int32 i2, j2, k2;

	if (x0 >= y0)
	{
		if (y0 >= z0)
		{
			i1 = 1;
			j1 = 0;
			k1 = 0;
			i2 = 1;
			j2 = 1;
			k2 = 0;
		}
		else if (x0 >= z0)
		{
			i1 = 1;
			j1 = 0;
			k1 = 0;
			i2 = 1;
			j2 = 0;
			k2 = 1;
		}
		else // x0 < z0
		{
			i1 = 0;
			j1 = 0;
			k1 = 1;
			i2 = 1;
			j2 = 0;
			k2 = 1;
		}
	}
	else // x0 < y0
	{
		if (y0 < z0)
		{
			i1 = 0;
			j1 = 0;
			k1 = 1;
			i2 = 0;
			j2 = 1;
			k2 = 1;
		}
		else if (x0 < z0)
		{
			i1 = 0;
			j1 = 1;
			k1 = 0;
			i2 = 0;
			j2 = 1;
			k2 = 1;
		}
		else // x0 >= z0
		{
			i1 = 0;
			j1 = 1;
			k1 = 0;
			i2 = 1;
			j2 = 1;
			k2 = 0;
		}
	}

	const float x1 = x0 - i1 + G3;
	const float y1 = y0 - j1 + G3;
	const float z1 = z0 - k1 + G3;
	const float x2 = x0 - i2 + F3;
	const float y2 = y0 - j2 + F3;
	const float z2 = z0 - k2 + F3;
	const float x3 = x0 + G33;
	const float y3 = y0 + G33;
	const float z3 = z0 + G33;

	float n0, n1, n2, n3;

	t = static_cast<float>(0.6) - x0 * x0 - y0 * y0 - z0 * z0;
	if (t < 0) n0 = 0;
	else
	{
		t *= t;
		n0 = t * t * GradCoord3D(Seed, i, j, k, x0, y0, z0);
	}

	t = static_cast<float>(0.6) - x1 * x1 - y1 * y1 - z1 * z1;
	if (t < 0) n1 = 0;
	else
	{
		t *= t;
		n1 = t * t * GradCoord3D(Seed, i + i1, j + j1, k + k1, x1, y1, z1);
	}

	t = static_cast<float>(0.6) - x2 * x2 - y2 * y2 - z2 * z2;
	if (t < 0) n2 = 0;
	else
	{
		t *= t;
		n2 = t * t * GradCoord3D(Seed, i + i2, j + j2, k + k2, x2, y2, z2);
	}

	t = static_cast<float>(0.6) - x3 * x3 - y3 * y3 - z3 * z3;
	if (t < 0) n3 = 0;
	else
	{
		t *= t;
		n3 = t * t * GradCoord3D(Seed, i + 1, j + 1, k + 1, x3, y3, z3);
	}

	return 32 * (n0 + n1 + n2 + n3);
}

float UNoiseBlueprintFunctionLibrary::GetSimplexFractal(const int32& Seed, const float& Frequency,
                                                        const float& Lacunarity, const float& Gain,
                                                        const int32& Octaves, const EFractalType& FractalType,
                                                        const FVector2D& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleSimplexFractalFBM(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::Billow:
		return SingleSimplexFractalBillow(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SingleSimplexFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SingleSimplexFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                              const int32& Octaves, FVector2D Coordinates)
{
	float sum = SingleSimplex(Seed, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SingleSimplex(++Seed, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleSimplexFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                                 const int32& Octaves, FVector2D Coordinates)
{
	float sum = FMath::Abs(SingleSimplex(Seed, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SingleSimplex(++Seed, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleSimplexFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                      const float& Gain, const int32& Octaves,
                                                                      FVector2D Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}

	float sig = 1 - FMath::Abs(SingleSimplex(Seed, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;
	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SingleSimplex(++Seed, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::SingleSimplexFractalBlend(int32 Seed, const float& Lacunarity, const float& Gain,
                                                                const int32& Octaves, FVector2D Coordinates)
{
	float sum = SingleSimplex(Seed, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum *= SingleSimplex(++Seed, Coordinates) * amp + 1;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::GetSimplex(const int32& Seed, const float& Frequency,
                                                 const FVector2D& Coordinates)
{
	return SingleSimplex(Seed, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SingleSimplex(const int32& Seed, const FVector2D& Coordinates)
{
	float t = (Coordinates.X + Coordinates.Y) * F2;
	const int32 i = FMath::FloorToInt(Coordinates.X + t);
	const int32 j = FMath::FloorToInt(Coordinates.Y + t);

	t = (i + j) * G2;
	const float X0 = i - t;
	const float Y0 = j - t;

	const float x0 = Coordinates.X - X0;
	const float y0 = Coordinates.Y - Y0;

	int32 i1, j1;
	if (x0 > y0)
	{
		i1 = 1;
		j1 = 0;
	}
	else
	{
		i1 = 0;
		j1 = 1;
	}

	const float x1 = x0 - i1 + G2;
	const float y1 = y0 - j1 + G2;
	const float x2 = x0 - 1 + F2;
	const float y2 = y0 - 1 + F2;

	float n0, n1, n2;

	t = static_cast<float>(0.5) - x0 * x0 - y0 * y0;
	if (t < 0) n0 = 0;
	else
	{
		t *= t;
		n0 = t * t * GradCoord2D(Seed, i, j, x0, y0);
	}

	t = static_cast<float>(0.5) - x1 * x1 - y1 * y1;
	if (t < 0) n1 = 0;
	else
	{
		t *= t;
		n1 = t * t * GradCoord2D(Seed, i + i1, j + j1, x1, y1);
	}

	t = static_cast<float>(0.5) - x2 * x2 - y2 * y2;
	if (t < 0) n2 = 0;
	else
	{
		t *= t;
		n2 = t * t * GradCoord2D(Seed, i + 1, j + 1, x2, y2);
	}

	return 50 * (n0 + n1 + n2);
}

float UNoiseBlueprintFunctionLibrary::GetSimplex(const int32& Seed, const float& Frequency, const FVector4& Coordinates)
{
	return SingleSimplex(Seed, Coordinates * Frequency);
}


float UNoiseBlueprintFunctionLibrary::SingleSimplex(const int32& Seed, const FVector4& Coordinates)
{
	float n0, n1, n2, n3, n4;
	float t = (Coordinates.X + Coordinates.Y + Coordinates.Z + Coordinates.W) * F4;
	const int32 i = FMath::FloorToInt(Coordinates.X + t);
	const int32 j = FMath::FloorToInt(Coordinates.Y + t);
	const int32 k = FMath::FloorToInt(Coordinates.Z + t);
	const int32 l = FMath::FloorToInt(Coordinates.W + t);
	t = (i + j + k + l) * G4;
	const float X0 = i - t;
	const float Y0 = j - t;
	const float Z0 = k - t;
	const float W0 = l - t;
	const float x0 = Coordinates.X - X0;
	const float y0 = Coordinates.Y - Y0;
	const float z0 = Coordinates.Z - Z0;
	const float w0 = Coordinates.W - W0;

	int32 c = (x0 > y0) ? 32 : 0;
	c += (x0 > z0) ? 16 : 0;
	c += (y0 > z0) ? 8 : 0;
	c += (x0 > w0) ? 4 : 0;
	c += (y0 > w0) ? 2 : 0;
	c += (z0 > w0) ? 1 : 0;
	c <<= 2;

	const int32 i1 = SIMPLEX_4D[c] >= 3 ? 1 : 0;
	const int32 i2 = SIMPLEX_4D[c] >= 2 ? 1 : 0;
	const int32 i3 = SIMPLEX_4D[c++] >= 1 ? 1 : 0;
	const int32 j1 = SIMPLEX_4D[c] >= 3 ? 1 : 0;
	const int32 j2 = SIMPLEX_4D[c] >= 2 ? 1 : 0;
	const int32 j3 = SIMPLEX_4D[c++] >= 1 ? 1 : 0;
	const int32 k1 = SIMPLEX_4D[c] >= 3 ? 1 : 0;
	const int32 k2 = SIMPLEX_4D[c] >= 2 ? 1 : 0;
	const int32 k3 = SIMPLEX_4D[c++] >= 1 ? 1 : 0;
	const int32 l1 = SIMPLEX_4D[c] >= 3 ? 1 : 0;
	const int32 l2 = SIMPLEX_4D[c] >= 2 ? 1 : 0;
	const int32 l3 = SIMPLEX_4D[c] >= 1 ? 1 : 0;

	const float x1 = x0 - i1 + G4;
	const float y1 = y0 - j1 + G4;
	const float z1 = z0 - k1 + G4;
	const float w1 = w0 - l1 + G4;
	const float x2 = x0 - i2 + 2 * G4;
	const float y2 = y0 - j2 + 2 * G4;
	const float z2 = z0 - k2 + 2 * G4;
	const float w2 = w0 - l2 + 2 * G4;
	const float x3 = x0 - i3 + 3 * G4;
	const float y3 = y0 - j3 + 3 * G4;
	const float z3 = z0 - k3 + 3 * G4;
	const float w3 = w0 - l3 + 3 * G4;
	const float x4 = x0 - 1 + 4 * G4;
	const float y4 = y0 - 1 + 4 * G4;
	const float z4 = z0 - 1 + 4 * G4;
	const float w4 = w0 - 1 + 4 * G4;

	t = static_cast<float>(0.6) - x0 * x0 - y0 * y0 - z0 * z0 - w0 * w0;
	if (t < 0) n0 = 0;
	else
	{
		t *= t;
		n0 = t * t * GradCoord4D(Seed, i, j, k, l, x0, y0, z0, w0);
	}
	t = static_cast<float>(0.6) - x1 * x1 - y1 * y1 - z1 * z1 - w1 * w1;
	if (t < 0) n1 = 0;
	else
	{
		t *= t;
		n1 = t * t * GradCoord4D(Seed, i + i1, j + j1, k + k1, l + l1, x1, y1, z1, w1);
	}
	t = static_cast<float>(0.6) - x2 * x2 - y2 * y2 - z2 * z2 - w2 * w2;
	if (t < 0) n2 = 0;
	else
	{
		t *= t;
		n2 = t * t * GradCoord4D(Seed, i + i2, j + j2, k + k2, l + l2, x2, y2, z2, w2);
	}
	t = static_cast<float>(0.6) - x3 * x3 - y3 * y3 - z3 * z3 - w3 * w3;
	if (t < 0) n3 = 0;
	else
	{
		t *= t;
		n3 = t * t * GradCoord4D(Seed, i + i3, j + j3, k + k3, l + l3, x3, y3, z3, w3);
	}
	t = static_cast<float>(0.6) - x4 * x4 - y4 * y4 - z4 * z4 - w4 * w4;
	if (t < 0) n4 = 0;
	else
	{
		t *= t;
		n4 = t * t * GradCoord4D(Seed, i + 1, j + 1, k + 1, l + 1, x4, y4, z4, w4);
	}

	return 27 * (n0 + n1 + n2 + n3 + n4);
}

// Cubic Noise
float UNoiseBlueprintFunctionLibrary::GetCubicFractal(const int32& Seed, const float& Frequency,
                                                      const float& Lacunarity, const float& Gain, const int32& Octaves,
                                                      const EFractalType& FractalType, const FVector& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleCubicFractalFBM(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::Billow:
		return SingleCubicFractalBillow(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SingleCubicFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SingleCubicFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                            const int32& Octaves, FVector Coordinates)
{
	float sum = SingleCubic(Seed, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SingleCubic(++Seed, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleCubicFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                               const int32& Octaves, FVector Coordinates)
{
	float sum = FMath::Abs(SingleCubic(Seed, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SingleCubic(++Seed, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleCubicFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                    const float& Gain, const int32& Octaves,
                                                                    FVector Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}

	float sig = 1 - FMath::Abs(SingleCubic(Seed, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;
	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SingleCubic(++Seed, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::GetCubic(const int32& Seed, const float& Frequency, const FVector& Coordinates)
{
	return SingleCubic(Seed, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SingleCubic(const int32& Seed, const FVector& Coordinates)
{
	const int32 x1 = FMath::FloorToInt(Coordinates.X);
	const int32 y1 = FMath::FloorToInt(Coordinates.Y);
	const int32 z1 = FMath::FloorToInt(Coordinates.Z);

	const int32 x0 = x1 - 1;
	const int32 y0 = y1 - 1;
	const int32 z0 = z1 - 1;
	const int32 x2 = x1 + 1;
	const int32 y2 = y1 + 1;
	const int32 z2 = z1 + 1;
	const int32 x3 = x1 + 2;
	const int32 y3 = y1 + 2;
	const int32 z3 = z1 + 2;

	const float xs = Coordinates.X - static_cast<float>(x1);
	const float ys = Coordinates.Y - static_cast<float>(y1);
	const float zs = Coordinates.Z - static_cast<float>(z1);

	return CubicLerp(
		CubicLerp(
			CubicLerp(ValCoord3D(Seed, x0, y0, z0), ValCoord3D(Seed, x1, y0, z0), ValCoord3D(Seed, x2, y0, z0),
			          ValCoord3D(Seed, x3, y0, z0), xs),
			CubicLerp(ValCoord3D(Seed, x0, y1, z0), ValCoord3D(Seed, x1, y1, z0), ValCoord3D(Seed, x2, y1, z0),
			          ValCoord3D(Seed, x3, y1, z0), xs),
			CubicLerp(ValCoord3D(Seed, x0, y2, z0), ValCoord3D(Seed, x1, y2, z0), ValCoord3D(Seed, x2, y2, z0),
			          ValCoord3D(Seed, x3, y2, z0), xs),
			CubicLerp(ValCoord3D(Seed, x0, y3, z0), ValCoord3D(Seed, x1, y3, z0), ValCoord3D(Seed, x2, y3, z0),
			          ValCoord3D(Seed, x3, y3, z0), xs),
			ys),
		CubicLerp(
			CubicLerp(ValCoord3D(Seed, x0, y0, z1), ValCoord3D(Seed, x1, y0, z1), ValCoord3D(Seed, x2, y0, z1),
			          ValCoord3D(Seed, x3, y0, z1), xs),
			CubicLerp(ValCoord3D(Seed, x0, y1, z1), ValCoord3D(Seed, x1, y1, z1), ValCoord3D(Seed, x2, y1, z1),
			          ValCoord3D(Seed, x3, y1, z1), xs),
			CubicLerp(ValCoord3D(Seed, x0, y2, z1), ValCoord3D(Seed, x1, y2, z1), ValCoord3D(Seed, x2, y2, z1),
			          ValCoord3D(Seed, x3, y2, z1), xs),
			CubicLerp(ValCoord3D(Seed, x0, y3, z1), ValCoord3D(Seed, x1, y3, z1), ValCoord3D(Seed, x2, y3, z1),
			          ValCoord3D(Seed, x3, y3, z1), xs),
			ys),
		CubicLerp(
			CubicLerp(ValCoord3D(Seed, x0, y0, z2), ValCoord3D(Seed, x1, y0, z2), ValCoord3D(Seed, x2, y0, z2),
			          ValCoord3D(Seed, x3, y0, z2), xs),
			CubicLerp(ValCoord3D(Seed, x0, y1, z2), ValCoord3D(Seed, x1, y1, z2), ValCoord3D(Seed, x2, y1, z2),
			          ValCoord3D(Seed, x3, y1, z2), xs),
			CubicLerp(ValCoord3D(Seed, x0, y2, z2), ValCoord3D(Seed, x1, y2, z2), ValCoord3D(Seed, x2, y2, z2),
			          ValCoord3D(Seed, x3, y2, z2), xs),
			CubicLerp(ValCoord3D(Seed, x0, y3, z2), ValCoord3D(Seed, x1, y3, z2), ValCoord3D(Seed, x2, y3, z2),
			          ValCoord3D(Seed, x3, y3, z2), xs),
			ys),
		CubicLerp(
			CubicLerp(ValCoord3D(Seed, x0, y0, z3), ValCoord3D(Seed, x1, y0, z3), ValCoord3D(Seed, x2, y0, z3),
			          ValCoord3D(Seed, x3, y0, z3), xs),
			CubicLerp(ValCoord3D(Seed, x0, y1, z3), ValCoord3D(Seed, x1, y1, z3), ValCoord3D(Seed, x2, y1, z3),
			          ValCoord3D(Seed, x3, y1, z3), xs),
			CubicLerp(ValCoord3D(Seed, x0, y2, z3), ValCoord3D(Seed, x1, y2, z3), ValCoord3D(Seed, x2, y2, z3),
			          ValCoord3D(Seed, x3, y2, z3), xs),
			CubicLerp(ValCoord3D(Seed, x0, y3, z3), ValCoord3D(Seed, x1, y3, z3), ValCoord3D(Seed, x2, y3, z3),
			          ValCoord3D(Seed, x3, y3, z3), xs),
			ys),
		zs) * CUBIC_3D_BOUNDING;
}


float UNoiseBlueprintFunctionLibrary::GetCubicFractal(const int32& Seed, const float& Frequency,
                                                      const float& Lacunarity, const float& Gain, const int32& Octaves,
                                                      const EFractalType& FractalType, const FVector2D& Coordinates)
{
	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleCubicFractalFBM(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::Billow:
		return SingleCubicFractalBillow(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	case EFractalType::RidgedMulti:
		return SingleCubicFractalRidgedMulti(Seed, Lacunarity, Gain, Octaves, Coordinates * Frequency);
	default:
		return 0;
	}
}

float UNoiseBlueprintFunctionLibrary::SingleCubicFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain,
                                                            const int32& Octaves, FVector2D Coordinates)
{
	float sum = SingleCubic(Seed, Coordinates);
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += SingleCubic(++Seed, Coordinates) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleCubicFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
                                                               const int32& Octaves, FVector2D Coordinates)
{
	float sum = FMath::Abs(SingleCubic(Seed, Coordinates)) * 2 - 1;
	float amp = 1;

	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 i = 0;

	while (++i < Octaves)
	{
		Coordinates *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SingleCubic(++Seed, Coordinates)) * 2 - 1) * amp;

		ampFractal += ampFB;
		ampFB *= Gain;
	}

	return sum * (1.0f / ampFractal);
}

float UNoiseBlueprintFunctionLibrary::SingleCubicFractalRidgedMulti(int32 Seed, const float& Lacunarity,
                                                                    const float& Gain, const int32& Octaves,
                                                                    FVector2D Coordinates)
{
	const float h = 1.0f;
	float frequency = 1.0f;

	const int32 MinOctaves = FMath::Clamp(Octaves, 1, Octaves);

	TArray<float> m_pSpectralWeights;
	m_pSpectralWeights.SetNumUninitialized(MinOctaves);

	for (int32 i = 0; i < MinOctaves; i++)
	{
		m_pSpectralWeights[i] = FMath::Pow(frequency, -h);
		frequency *= Lacunarity;
	}

	float sig = 1 - FMath::Abs(SingleCubic(Seed, Coordinates));
	sig *= sig;
	float sum = sig * m_pSpectralWeights[0];
	float amp = sig * Gain;

	if (amp > 1.0f)
	{
		amp = 1.0f;
	}
	if (amp < 0.0f)
	{
		amp = 0.0f;
	}
	int32 i = 0;

	while (++i < MinOctaves)
	{
		Coordinates *= Lacunarity;
		sig = 1 - FMath::Abs(SingleCubic(++Seed, Coordinates));
		sig *= sig;
		sig *= amp;

		amp = sig * Gain;
		if (amp > 1.0f)
		{
			amp = 1.0f;
		}
		if (amp < 0.0f)
		{
			amp = 0.0f;
		}


		sum += (sig * m_pSpectralWeights[i]);
	}
	return (sum * 1.25f) - 1.0f;
}

float UNoiseBlueprintFunctionLibrary::GetCubic(const int32& Seed, const float& Frequency, const FVector2D& Coordinates)
{
	return SingleCubic(Seed, Coordinates * Frequency);
}

float UNoiseBlueprintFunctionLibrary::SingleCubic(const int32& Seed, const FVector2D& Coordinates)
{
	const int32 x1 = FMath::FloorToInt(Coordinates.X);
	const int32 y1 = FMath::FloorToInt(Coordinates.Y);

	const int32 x0 = x1 - 1;
	const int32 y0 = y1 - 1;
	const int32 x2 = x1 + 1;
	const int32 y2 = y1 + 1;
	const int32 x3 = x1 + 2;
	const int32 y3 = y1 + 2;

	float xs = Coordinates.X - static_cast<float>(x1);
	float ys = Coordinates.Y - static_cast<float>(y1);

	return CubicLerp(
		CubicLerp(ValCoord2D(Seed, x0, y0), ValCoord2D(Seed, x1, y0), ValCoord2D(Seed, x2, y0),
		          ValCoord2D(Seed, x3, y0),
		          xs),
		CubicLerp(ValCoord2D(Seed, x0, y1), ValCoord2D(Seed, x1, y1), ValCoord2D(Seed, x2, y1),
		          ValCoord2D(Seed, x3, y1),
		          xs),
		CubicLerp(ValCoord2D(Seed, x0, y2), ValCoord2D(Seed, x1, y2), ValCoord2D(Seed, x2, y2),
		          ValCoord2D(Seed, x3, y2),
		          xs),
		CubicLerp(ValCoord2D(Seed, x0, y3), ValCoord2D(Seed, x1, y3), ValCoord2D(Seed, x2, y3),
		          ValCoord2D(Seed, x3, y3),
		          xs),
		ys) * CUBIC_2D_BOUNDING;
}

void UNoiseBlueprintFunctionLibrary::GradientPerturb(const int32& Seed, const float& Perturb, const float& Frequency,
                                                     const EInterp& Interpolation, FVector& Coordinates)
{
	SingleGradientPerturb(Seed, Perturb, Frequency, Interpolation, Coordinates);
}

void UNoiseBlueprintFunctionLibrary::GradientPerturbFractal(int32 Seed, const float& Perturb, const float& Frequency,
                                                            const float& Lacunarity, const float& Gain,
                                                            const int32& Octaves, const EInterp& Interpolation,
                                                            FVector& Coordinates)
{
	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 ii = 0;
	while (++ii < Octaves)
	{
		ampFractal += ampFB;
		ampFB *= Gain;
	}

	float amp = Perturb * (1.0f / ampFractal);
	float freq = Frequency;

	int32 i = 0;

	SingleGradientPerturb(Seed, amp, Frequency, Interpolation, Coordinates);

	while (++i < Octaves)
	{
		freq *= Lacunarity;
		amp *= Gain;
		SingleGradientPerturb(++Seed, amp, freq, Interpolation, Coordinates);
	}
}

void UNoiseBlueprintFunctionLibrary::SingleGradientPerturb(const int32& Seed, const float& Perturb,
                                                           const float& Frequency, const EInterp& Interpolation,
                                                           FVector& Coordinates)
{
	const float xf = Coordinates.X * Frequency;
	const float yf = Coordinates.Y * Frequency;
	const float zf = Coordinates.Z * Frequency;

	const int32 x0 = FMath::FloorToInt(xf);
	const int32 y0 = FMath::FloorToInt(yf);
	const int32 z0 = FMath::FloorToInt(zf);
	const int32 x1 = x0 + 1;
	const int32 y1 = y0 + 1;
	const int32 z1 = z0 + 1;

	float xs, ys, zs;
	switch (Interpolation)
	{
	default:
	case EInterp::Linear:
		xs = xf - x0;
		ys = yf - y0;
		zs = zf - z0;
		break;
	case EInterp::Hermite:
		xs = InterpHermiteFunc(xf - x0);
		ys = InterpHermiteFunc(yf - y0);
		zs = InterpHermiteFunc(zf - z0);
		break;
	case EInterp::Quintic:
		xs = InterpQuinticFunc(xf - x0);
		ys = InterpQuinticFunc(yf - y0);
		zs = InterpQuinticFunc(zf - z0);
		break;
	}

	FVector vec0 = CELL_3D[Hash3D(Seed, x0, y0, z0) & 255];
	FVector vec1 = CELL_3D[Hash3D(Seed, x1, y0, z0) & 255];

	float lx0x = FMath::Lerp(vec0.X, vec1.X, xs);
	float ly0x = FMath::Lerp(vec0.Y, vec1.Y, xs);
	float lz0x = FMath::Lerp(vec0.Z, vec1.Z, xs);

	vec0 = CELL_3D[Hash3D(Seed, x0, y1, z0) & 255];
	vec1 = CELL_3D[Hash3D(Seed, x1, y1, z0) & 255];

	float lx1x = FMath::Lerp(vec0.X, vec1.X, xs);
	float ly1x = FMath::Lerp(vec0.Y, vec1.Y, xs);
	float lz1x = FMath::Lerp(vec0.Z, vec1.Z, xs);

	const float lx0y = FMath::Lerp(lx0x, lx1x, ys);
	const float ly0y = FMath::Lerp(ly0x, ly1x, ys);
	const float lz0y = FMath::Lerp(lz0x, lz1x, ys);

	vec0 = CELL_3D[Hash3D(Seed, x0, y0, z1) & 255];
	vec1 = CELL_3D[Hash3D(Seed, x1, y0, z1) & 255];

	lx0x = FMath::Lerp(vec0.X, vec1.X, xs);
	ly0x = FMath::Lerp(vec0.Y, vec1.Y, xs);
	lz0x = FMath::Lerp(vec0.Z, vec1.Z, xs);

	vec0 = CELL_3D[Hash3D(Seed, x0, y1, z1) & 255];
	vec1 = CELL_3D[Hash3D(Seed, x1, y1, z1) & 255];

	lx1x = FMath::Lerp(vec0.X, vec1.X, xs);
	ly1x = FMath::Lerp(vec0.Y, vec1.Y, xs);
	lz1x = FMath::Lerp(vec0.Z, vec1.Z, xs);

	Coordinates.X += FMath::Lerp(lx0y, FMath::Lerp(lx0x, lx1x, ys), zs) * Perturb;
	Coordinates.Y += FMath::Lerp(ly0y, FMath::Lerp(ly0x, ly1x, ys), zs) * Perturb;
	Coordinates.Z += FMath::Lerp(lz0y, FMath::Lerp(lz0x, lz1x, ys), zs) * Perturb;
}

void UNoiseBlueprintFunctionLibrary::GradientPerturb(const int32& Seed, const float& Perturb, const float& Frequency,
                                                     const EInterp& Interpolation, FVector2D& Coordinates)
{
	SingleGradientPerturb(Seed, Perturb, Frequency, Interpolation, Coordinates);
}

void UNoiseBlueprintFunctionLibrary::GradientPerturbFractal(int32 Seed, const float& Perturb, const float& Frequency,
                                                            const float& Lacunarity, const float& Gain,
                                                            const int32& Octaves, const EInterp& Interpolation,
                                                            FVector2D& Coordinates)
{
	float ampFB = Gain;
	float ampFractal = 1.0f;

	int32 ii = 0;
	while (++ii < Octaves)
	{
		ampFractal += ampFB;
		ampFB *= Gain;
	}

	float amp = Perturb * (1.0f / ampFractal);
	float freq = Frequency;
	int32 i = 0;

	SingleGradientPerturb(Seed, amp, Frequency, Interpolation, Coordinates);

	while (++i < Octaves)
	{
		freq *= Lacunarity;
		amp *= Gain;
		SingleGradientPerturb(++Seed, amp, freq, Interpolation, Coordinates);
	}
}

void UNoiseBlueprintFunctionLibrary::SingleGradientPerturb(const int32& Seed, const float& Perturb,
                                                           const float& Frequency, const EInterp& Interpolation,
                                                           FVector2D& Coordinates)
{
	const float xf = Coordinates.X * Frequency;
	const float yf = Coordinates.Y * Frequency;

	const int32 x0 = FMath::FloorToInt(xf);
	const int32 y0 = FMath::FloorToInt(yf);
	const int32 x1 = x0 + 1;
	const int32 y1 = y0 + 1;

	float xs, ys;
	switch (Interpolation)
	{
	default:
	case EInterp::Linear:
		xs = xf - x0;
		ys = yf - y0;
		break;
	case EInterp::Hermite:
		xs = InterpHermiteFunc(xf - x0);
		ys = InterpHermiteFunc(yf - y0);
		break;
	case EInterp::Quintic:
		xs = InterpQuinticFunc(xf - x0);
		ys = InterpQuinticFunc(yf - y0);
		break;
	}

	FVector2D vec0 = CELL_2D[Hash2D(Seed, x0, y0) & 255];
	FVector2D vec1 = CELL_2D[Hash2D(Seed, x1, y0) & 255];

	const float lx0x = FMath::Lerp(vec0.X, vec1.X, xs);
	const float ly0x = FMath::Lerp(vec0.Y, vec1.Y, xs);

	vec0 = CELL_2D[Hash2D(Seed, x0, y1) & 255];
	vec1 = CELL_2D[Hash2D(Seed, x1, y1) & 255];

	const float lx1x = FMath::Lerp(vec0.X, vec1.X, xs);
	const float ly1x = FMath::Lerp(vec0.Y, vec1.Y, xs);

	Coordinates.X += FMath::Lerp(lx0x, lx1x, ys) * Perturb;
	Coordinates.Y += FMath::Lerp(ly0x, ly1x, ys) * Perturb;
}


float UNoiseBlueprintFunctionLibrary::GetValue2D(int32 Seed, float Frequency, EInterp Interpolation,
                                                 const FVector2D& Coordinates)
{
	return GetValue(Seed, Frequency, Interpolation, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetValueFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                        int32 Octaves, EInterp Interpolation, EFractalType FractalType,
                                                        const FVector2D& Coordinates)
{
	return GetValueFractal(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetPerlin2D(int32 Seed, float Frequency, EInterp Interpolation,
                                                  const FVector2D& Coordinates)
{
	return GetPerlin(Seed, Frequency, Interpolation, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetPerlinFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                         int32 Octaves, EInterp Interpolation, EFractalType FractalType,
                                                         const FVector2D& Coordinates)
{
	return GetPerlinFractal(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetSimplex2D(int32 Seed, float Frequency, const FVector2D& Coordinates)
{
	return GetSimplex(Seed, Frequency, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetSimplexFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                          int32 Octaves, EFractalType FractalType,
                                                          const FVector2D& Coordinates)
{
	return GetSimplexFractal(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetSimplexFractalBlend(int32 Seed, float Lacunarity, float Gain, int32 Octaves,
                                                             const FVector2D& Coordinates)
{
	return SingleSimplexFractalBlend(Seed, Lacunarity, Gain, Octaves, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetWhiteNoise2D(int32 Seed, const FVector2D& Coordinates)
{
	return GetWhiteNoise(Seed, Coordinates.X, Coordinates.Y);
}

float UNoiseBlueprintFunctionLibrary::GetCubic2D(int32 Seed, float Frequency, const FVector2D& Coordinates)
{
	return GetCubic(Seed, Frequency, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetCubicFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                        int32 Octaves, EFractalType FractalType,
                                                        const FVector2D& Coordinates)
{
	return GetCubicFractal(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates);
}

void UNoiseBlueprintFunctionLibrary::GradientPerturb2D(int32 Seed, float Perturb, float Frequency,
                                                       EInterp Interpolation, const FVector2D& Coordinates,
                                                       FVector2D& OutCoordinates)
{
	OutCoordinates = Coordinates;
	GradientPerturb(Seed, Perturb, Frequency, Interpolation, OutCoordinates);
}

void UNoiseBlueprintFunctionLibrary::GradientPerturbFractal2D(int32 Seed, float Perturb, float Frequency,
                                                              float Lacunarity, float Gain, int32 Octaves,
                                                              EInterp Interpolation, const FVector2D& Coordinates,
                                                              FVector2D& OutCoordinates)
{
	OutCoordinates = Coordinates;
	GradientPerturbFractal(Seed, Perturb, Frequency, Lacunarity, Gain, Octaves, Interpolation, OutCoordinates);
}

float UNoiseBlueprintFunctionLibrary::GetValue3D(int32 Seed, float Frequency, EInterp Interpolation,
                                                 const FVector& Coordinates)
{
	return GetValue(Seed, Frequency, Interpolation, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetValueFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                        int32 Octaves, EInterp Interpolation, EFractalType FractalType,
                                                        const FVector& Coordinates)
{
	return GetValueFractal(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetPerlin3D(int32 Seed, float Frequency, EInterp Interpolation,
                                                  const FVector& Coordinates)
{
	return GetPerlin(Seed, Frequency, Interpolation, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetPerlinFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                         int32 Octaves, EInterp Interpolation, EFractalType FractalType,
                                                         const FVector& Coordinates)
{
	return GetPerlinFractal(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetSimplex3D(int32 Seed, float Frequency, const FVector& Coordinates)
{
	return GetSimplex(Seed, Frequency, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetSimplexFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                          int32 Octaves, EFractalType FractalType,
                                                          const FVector& Coordinates)
{
	return GetSimplexFractal(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetWhiteNoise3D(int32 Seed, const FVector& Coordinates)
{
	return GetWhiteNoise(Seed, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UNoiseBlueprintFunctionLibrary::GetCubic3D(int32 Seed, float Frequency, const FVector& Coordinates)
{
	return GetCubic(Seed, Frequency, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetCubicFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain,
                                                        int32 Octaves, EFractalType FractalType,
                                                        const FVector& Coordinates)
{
	return GetCubicFractal(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates);
}

void UNoiseBlueprintFunctionLibrary::GradientPerturb3D(int32 Seed, float Perturb, float Frequency,
                                                       EInterp Interpolation, const FVector& Coordinates,
                                                       FVector& OutCoordinates)
{
	OutCoordinates = Coordinates;
	GradientPerturb(Seed, Perturb, Frequency, Interpolation, OutCoordinates);
}

void UNoiseBlueprintFunctionLibrary::GradientPerturbFractal3D(int32 Seed, float Perturb, float Frequency,
                                                              float Lacunarity, float Gain, int32 Octaves,
                                                              EInterp Interpolation, const FVector& Coordinates,
                                                              FVector& OutCoordinates)
{
	OutCoordinates = Coordinates;
	GradientPerturbFractal(Seed, Perturb, Frequency, Lacunarity, Gain, Octaves, Interpolation, OutCoordinates);
}

float UNoiseBlueprintFunctionLibrary::GetSimplex4D(int32 Seed, float Frequency, const FVector4& Coordinates)
{
	return GetSimplex(Seed, Frequency, Coordinates);
}

float UNoiseBlueprintFunctionLibrary::GetWhiteNoise4D(int32 Seed, FVector4 Coordinates)
{
	return GetWhiteNoise(Seed, Coordinates.X, Coordinates.Y, Coordinates.Z, Coordinates.W);
}


float UNoiseBlueprintFunctionLibrary::SelectNoise(float NoiseValue1, float NoiseValue2, float ControlNoise,
                                                  ESelectInterpType Interpolation, float Falloff, float Threshold,
                                                  int32 Steps)
{
	if (Interpolation != ESelectInterpType::None)
	{
		if (ControlNoise <= (Threshold - Falloff))
		{
			return NoiseValue2;
		}
		if (ControlNoise >= (Threshold + Falloff))
		{
			return NoiseValue1;
		}
		switch (Interpolation)
		{
		case ESelectInterpType::CircularIn:
			return FMath::InterpCircularIn(NoiseValue2, NoiseValue1,
			                               (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::CircularInOut:
			return FMath::InterpCircularInOut(NoiseValue2, NoiseValue1,
			                                  (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::CircularOut:
			return FMath::InterpCircularOut(NoiseValue2, NoiseValue1,
			                                (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::ExponentialIn:
			return FMath::InterpExpoIn(NoiseValue2, NoiseValue1,
			                           (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::ExponentialInOut:
			return FMath::InterpExpoInOut(NoiseValue2, NoiseValue1,
			                              (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::ExponentialOut:
			return FMath::InterpExpoOut(NoiseValue2, NoiseValue1,
			                            (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::SineIn:
			return FMath::InterpSinIn(NoiseValue2, NoiseValue1,
			                          (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::SineInOut:
			return FMath::InterpSinInOut(NoiseValue2, NoiseValue1,
			                             (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::SineOut:
			return FMath::InterpSinOut(NoiseValue2, NoiseValue1,
			                           (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		case ESelectInterpType::Step:
			return FMath::InterpStep(NoiseValue2, NoiseValue1,
			                         (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)), Steps);
		case ESelectInterpType::Linear:
			return FMath::Lerp(NoiseValue2, NoiseValue1, (ControlNoise - (Threshold - Falloff) / (2.0f * Falloff)));
		}
	}
	if (ControlNoise > Threshold)
	{
		return NoiseValue1;
	}
	return NoiseValue2;
}

float UNoiseBlueprintFunctionLibrary::BlendNoise(float NoiseValue1, float NoiseValue2, float ControlNoise,
                                                 UCurveFloat* BlendCurve)
{
	if (BlendCurve)
	{
		return FMath::Lerp(NoiseValue1, NoiseValue2, BlendCurve->GetFloatValue(ControlNoise));
	}

	return FMath::Lerp(NoiseValue1, NoiseValue2, ControlNoise);
}

float UNoiseBlueprintFunctionLibrary::ScaleBiasNoise(float NoiseValue, float Scale, float Bias)
{
	return (NoiseValue * Scale) + Bias;
}

float UNoiseBlueprintFunctionLibrary::AddNoise(float NoiseValue1, float NoiseValue2, float MaskNoise, float Threshold)
{
	float Modifier = 1.0f;
	if (MaskNoise >= Threshold)
	{
		Modifier = MaskNoise;
	}
	else
	{
		return NoiseValue1;
	}

	return Modifier * (NoiseValue1 + NoiseValue2);
}

float UNoiseBlueprintFunctionLibrary::Select3Noise(float NoiseValue1, float NoiseValue2, float NoiseValue3,
                                                   float ControlNoise, ESelectInterpType Interpolation, float Falloff,
                                                   float LowerThreshold /*= 0.0f*/, float UpperThreshold, int32 Steps)
{
	if (ControlNoise >= UpperThreshold)
	{
		return NoiseValue1;
	}
	if (ControlNoise < UpperThreshold && ControlNoise >= LowerThreshold)
	{
		return NoiseValue2;
	}
	return NoiseValue3;
}

float UNoiseBlueprintFunctionLibrary::RadialNoise(float NoiseValue1, float NoiseValue2, ESelectInterpType Interpolation,
                                                  FVector Origin, float Radius, float Falloff, int32 Steps,
                                                  const FVector& Coordinates)
{
	float dist = (Origin - Coordinates).Size();

	if (Interpolation != ESelectInterpType::None)
	{
		if (dist > Radius + Falloff)
		{
			return NoiseValue2;
		}
		if (dist < Radius)
		{
			return NoiseValue1;
		}
		switch (Interpolation)
		{
		case ESelectInterpType::CircularIn:
			return FMath::InterpCircularIn(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::CircularInOut:
			return FMath::InterpCircularInOut(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::CircularOut:
			return FMath::InterpCircularOut(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::ExponentialIn:
			return FMath::InterpExpoIn(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::ExponentialInOut:
			return FMath::InterpExpoInOut(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::ExponentialOut:
			return FMath::InterpExpoOut(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::SineIn:
			return FMath::InterpSinIn(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::SineInOut:
			return FMath::InterpSinInOut(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::SineOut:
			return FMath::InterpSinInOut(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		case ESelectInterpType::Step:
			return FMath::InterpStep(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff, Steps);
		case ESelectInterpType::Linear:
			return FMath::Lerp(NoiseValue1, NoiseValue2, (dist - Radius) / Falloff);
		}
	}

	if (dist > Radius)
	{
		return NoiseValue1;
	}
	return NoiseValue2;
}
