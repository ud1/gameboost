/** \file
 \brief Исходный шейдер класса IRenderCubemapEnvironment
 
  \autor  ksacvet777
 */

 
 
float4x4 matWorld  = float4x4( 1.00, 0.00, 0.00, 0.00, 
								0.00, 1.00, 0.00, 0.00, 
								0.00, 0.00, 1.00, 0.00, 
								0.00, 0.00, 0.00, 1.00 );
								
float4x4 matViewInverse : ViewInverse;
float4x4 matViewProj : ViewProjection;
 
struct VS_OUTPUT 
 {
   float4 Pos: POSITION;
   float3 pos: TEXCOORD0;
 };

VS_OUTPUT  vs_main(float4 Pos: POSITION)
{
   VS_OUTPUT Out;
        
   float4x4 matNew = matWorld;
 matNew[0][3] +=  matViewInverse[0][3]; 
 matNew[1][3] +=  matViewInverse[1][3]; 
 matNew[2][3] +=  matViewInverse[2][3]; 
 
  float4x4 mwvp = mul(matViewProj, matNew);
        Out.Pos = mul(mwvp, Pos);
 
   Out.pos = Pos.yzx;

   return Out;
}
 

float envirBri  = float( 1.06 );
float4 colorCube
<
   string UIName = "colorCube";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.96, 0.95, 1.00, 1.00 );

texture cubemap_Tex ;

sampler skyBox = sampler_state
{
   Texture = (cubemap_Tex);
   ADDRESSU = CLAMP;
   ADDRESSV = CLAMP;
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
};

float4  ps_main(float3 pos: TEXCOORD0) : COLOR 
{
   return texCUBE(skyBox, pos) * colorCube * envirBri; 
}
 
technique cubeEnvir
{
   pass pass0
   {
      ZENABLE = FALSE;
      CULLMODE = CW;

      VertexShader = compile vs_2_0  vs_main();
      PixelShader = compile vs_2_0 ps_main();
   }

}
