


pipeline {
	agent any

	environment {
		BUILD_DIR = "jenkins-cmake-build"
	}

	stages {

		stage("SCM CHECKOUT") {
			steps {
				checkout scm
			}
			steps {
				sh """
				 echo 'Recuperation du code depuis github'
				"""
			}
		}

		stage("CONFIG") {
			steps {
				sh """
					mkdir -p ${BUILD_DIR};
					cd ${BUILD_DIR};
					cmake -G Ninja ..;
				"""
			}
		}

		stage("BUILDING") {
			steps {
				sh """
					cd ${BUILD_DIR};
					ninja;
				"""
			}
		}

		stage("TESTS") {
			steps {

			}
		}

		stage("SAMPLES") {
			steps {

			}
		}

	}
	post {
		always {
			cleanWs()
		}
	}
}

