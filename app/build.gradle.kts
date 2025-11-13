plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "com.example.edgedetect"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.edgedetect"
        minSdk = 24
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            // Consider enabling minification and proguard rules in a real release build:
            isMinifyEnabled = false
            // shrinkResources = true // enable when minify is enabled
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }

    // Java / Kotlin compatibility
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
    kotlinOptions {
        // targeting Java 11 is compatible with recent Android Gradle Plugin versions
        jvmTarget = "11"
    }

    // Useful build features for many Android apps (enable viewBinding for easier view access)
    buildFeatures {
        viewBinding = true
    }

    // Reduce packaging collisions from some libraries
    packagingOptions {
        resources {
            excludes += setOf("META-INF/AL2.0", "META-INF/LGPL2.1")
        }
    }
}

dependencies {
    // Core libraries
    implementation("androidx.core:core-ktx:1.12.0")
    implementation("androidx.appcompat:appcompat:1.6.1")
    implementation("com.google.android.material:material:1.9.0")

    // Camera: use BOM to keep camera component versions aligned
    implementation(platform("androidx.camera:camera-bom:1.3.1"))
    implementation("androidx.camera:camera-core")
    implementation("androidx.camera:camera-camera2")
    implementation("androidx.camera:camera-lifecycle")
    // Optional: camera-view or camera-extensions if you need PreviewView / extensions:
    implementation("androidx.camera:camera-view:1.3.0") // add if using PreviewView helper

    // Lifecycle / Activity
    implementation("androidx.activity:activity-ktx:1.8.0")
    implementation("androidx.lifecycle:lifecycle-runtime-ktx:2.6.1")

    // Coroutines
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-android:1.7.3")

    // Tests
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")
}
