#version 410 core

//Definitions
struct LightInfo {
    vec3 position;
    vec3 ambientLightIntensity;
    vec3 diffuseLightIntensity;
    vec3 specularLightIntensity;
};

struct MaterialInfo {
    float specularReflectionConstant;
    float diffuseReflectionConstant;
    float ambientReflectionConstant;
    float alfa;
};

//Variable in
layout(location = 0) in float vsTextureCoordinate;
layout(location = 1) in vec3 vsNormal;
layout(location = 2) in vec3 vsPosition;
layout(location = 3) in float vsLocalAlpha;

//Variable out
out vec4 fColor;

//Uniform in
uniform sampler1D colormap;
uniform int lightModel;
uniform float globalAlpha;


//Constants
vec3 eye = vec3(2000.0, 5000.0, -1000.0);
LightInfo light = LightInfo(vec3(-2000.0, 5000.0, 1000.0), vec3(1.0), vec3(10.0), vec3(1.0));
MaterialInfo material = MaterialInfo(0.3, 0.5, 0.4, 150.0);

//Auxilary Functions
vec3 unitVectorToColor(vec3 vector){
        return (vector + vec3(1)) / 2.0;
}

vec3 frontLightMaterial(float reflectionConstant, vec3 color, vec3 light)
{
    return clamp(light * (reflectionConstant * color), 0.0, 1.0);
}

float computeAlpha(){
    return clamp(vsLocalAlpha * globalAlpha, 0.0, 1.0);
}

//Lighting Model Functions
void noLight(){
    vec4 color = texture(colormap, vsTextureCoordinate);
    color.a = computeAlpha();
    fColor = color;
}

void phongLight(){
    vec3 viewVector = normalize(eye - vsPosition);
    vec3 lightVector = normalize(light.position - vsPosition);
    vec3 reflectionVector = normalize(reflect(-lightVector, vsNormal));

    vec3 materialColor = texture(colormap, vsTextureCoordinate).xyz;

    vec3 ambient = frontLightMaterial(
        material.ambientReflectionConstant, 
        materialColor, 
        light.ambientLightIntensity);

    float diffuseDotProduct = dot(vsNormal, lightVector);
    vec3 diffuse = frontLightMaterial(
        material.diffuseReflectionConstant, 
        materialColor, 
        light.diffuseLightIntensity) * max(diffuseDotProduct, 0.0);
    vec3 specular;
    if(diffuseDotProduct > 0){
        vec3 specular = frontLightMaterial(
            material.specularReflectionConstant,
            materialColor,
            light.specularLightIntensity) * pow(max(dot(reflectionVector, viewVector), 0.0 ), material.alfa);
    }
    vec3 phongColor = clamp(
        vec3(0.0) 
        + ambient 
        + diffuse 
        + specular
        , 
        0, 1);
    fColor = vec4(phongColor, computeAlpha());
}

void main(void)
{
    if(lightModel == 0) noLight();
    if(lightModel == 1) phongLight();
}
