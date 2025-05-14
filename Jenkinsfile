


pipeline {
	agent any

	environment {
		BUILD_DIR = "${WORKSPACE}/jenkins-cmake-build"
	}

	stages {

		stage("SCM CHECKOUT") {
			steps {
				checkout scm
			}
		}

		stage("CONFIG") {
			steps {
				sh """
					mkdir -p ${BUILD_DIR};
					cd ${BUILD_DIR};
					cmake -G Ninja '../core-24/';
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

		// stage("TESTS") {
		//	steps {
		//	}
		// }

		// stage("SAMPLES") {
		// 	steps {
		//	}
		//}

	}
	post {
		always {
			cleanWs()
		}
	}
}

