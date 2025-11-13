plugins {
    // Named version variables make it easier to update versions in one place.
    // Consider moving these into settings.gradle.kts (pluginManagement) or a version catalog (gradle/libs.versions.toml).
    val agpVersion = "8.2.0"
    val kotlinVersion = "1.9.20"

    id("com.android.application") version agpVersion apply false
    id("org.jetbrains.kotlin.android") version kotlinVersion apply false
}

buildscript {
    // Ensure plugin resolution repositories are available for environments that don't use settings pluginManagement.
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
    }
}

tasks.register("clean", Delete::class) {
    group = "build"
    description = "Removes the root project's build directory."
    delete(rootProject.buildDir)
}
