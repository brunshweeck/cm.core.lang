pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('CONFIGURATION') {
            steps {
              sh 'mkdir cmake-build-debug'
              sh 'cd cmake-build-debug'
              sh 'cmake -DCMAKE_BUILD_TYPE=Debug ..'
            }
        }
        stage('BUILD') {
            steps {
                sh 'cmake --build .'
            }
        }
        // stage('TESTS') {
        //     steps {
        //         sh './test.sh' // Remplace par ta commande de test (si tu en as)
        //     }
        // }
      stage('CLEARNING') {
        steps {
          deleteDir()
        }
      }
    }
}
