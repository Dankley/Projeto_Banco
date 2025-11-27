#!/bin/bash

# Script de teste do sistema bancário

echo "================= TESTE DO SISTEMA BANCÁRIO ================="
echo ""
echo "Testando as seguintes operações:"
echo "1. Abertura de conta"
echo "2. Depósito"
echo "3. Consulta de saldo"
echo "4. Saque"
echo "5. Listagem de contas"
echo ""
echo "=============================================================="
echo ""

# Criar arquivo de entrada para o programa
cat > /tmp/entrada_teste.txt << 'EOF'
1
Maria Santos
98765432101234
21987654321
1
2
50
5
1
1
001
3
1
50
5
1
1
001
7
3
9
EOF

# Executar o programa com as entradas de teste
/workspaces/Projeto_Banco/sistema_bancario < /tmp/entrada_teste.txt
